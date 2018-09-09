#pragma once

#include <vector>
#include <list>

#ifndef _WIN32
#import <CoreFoundation/CoreFoundation.h>
#endif

#if defined(_WIN64)
 typedef unsigned __int64 UINT_PTR;
#else
 typedef unsigned int UINT_PTR;
#endif


/*
This class provides a programmable timer for creating animation effects.
This is needed for GUI Modules based on SeGuiCompositedGfxBase, these can't easily use regular WM_TIMER
because they don't have a native Window Handle(HWND).

NOTE: all instances of the module share the same timer, and therefore the same timer interval.
*/

class TimerClient
{
public:
	virtual ~TimerClient();
	virtual bool OnTimer() = 0;

	// New. Better
	void StartTimer(int periodMilliSeconds);
	void StopTimer();

	// old. avoid.
	void SetTimerIntervalMs( int periodMilliSeconds );
	void StartTimer();
};

typedef std::vector<class TimerClient*> clientContainer_t;

namespace se_sdk_timers
{
#ifdef _WIN32
    typedef UINT_PTR timer_id_t;
#else
    typedef void* timer_id_t;
 #endif
    
class Timer
{
public:
    timer_id_t idleTimer_;
	int periodMilliSeconds;
	clientContainer_t clients_;

	Timer(int pPeriodMilliSeconds = 50) :
		periodMilliSeconds(pPeriodMilliSeconds)
		, idleTimer_(0)
	{}
	void Start();
	void Stop();
	void OnTimer();
};

}

class TimerManager
{
//	std::vector< se_sdk_timers::Timer > timers; // !! invalidated object being iterated in OnTimer() when resizing vector to add new stuff.
	std::list< se_sdk_timers::Timer > timers;

public:
	TimerManager(void);
	static TimerManager* Instance();
	void RegisterClient(TimerClient* client, int periodMilliSeconds);

	void RegisterClient(TimerClient* client)
	{
		RegisterClient(client, interval_);
	}
	void UnRegisterClient( TimerClient* client );
	void SetInterval( int intervalMs );
	~TimerManager(void);
    void OnTimer(se_sdk_timers::timer_id_t timerId);

private:
	int interval_;
};
