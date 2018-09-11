#pragma once
#include "../se_sdk3/mp_sdk_audio.h"
#include "KarplusStrongDelayLine.h"

#define MAX_DELAY_MS 80.0
#define INITIAL_DELAY_MS (1000.0/440.0)
#define INITIAL_DRY_FRACTION 0.0f
#define INITIAL_FEEDBACK_FRACTION 1.0f

class Karplus_strong_delay: public MpBase
{
public:
	Karplus_strong_delay(IMpUnknown* host);
    int32_t MP_STDCALL open() override;
	void subProcess(int bufferOffset, int sampleFrames);
	virtual void onSetPins(void);

private:
	AudioInPin pinInput;
	AudioInPin pinPitch, pinFeedback;
	AudioOutPin pinOutput;

    KarplusStrongDelayLine delayLine;
};
