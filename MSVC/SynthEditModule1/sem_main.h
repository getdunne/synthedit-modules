#pragma once
#include "../se_sdk3/mp_sdk_audio.h"

class $safeprojectname$: public MpBase
{
public:
	$safeprojectname$(IMpUnknown* host);
    int32_t MP_STDCALL open() override;
	void subProcess(int bufferOffset, int sampleFrames);
	virtual void onSetPins(void);

private:
	AudioInPin pinInput;
	AudioOutPin pinOutput;
};
