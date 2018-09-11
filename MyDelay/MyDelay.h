#pragma once
#include "../se_sdk3/mp_sdk_audio.h"
#include "AdjustableDelayLine.hpp"

#define MAX_DELAY_MS 1000.0
#define INITIAL_DELAY_MS 500.0
#define INITIAL_DRY_FRACTION 1.0f
#define INITIAL_FEEDBACK_FRACTION 0.3f

class MyDelay: public MpBase
{
public:
	MyDelay(IMpUnknown* host);
    int32_t MP_STDCALL open() override;
	void subProcess(int bufferOffset, int sampleFrames);
	virtual void onSetPins(void);

private:
	AudioInPin pinInput1;
	AudioInPin pinDelaySec, pinDryFraction, pinFeedback;
	AudioOutPin pinOutput1;

    AudioKitCore::AdjustableDelayLine delayLine;
};
