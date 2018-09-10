#include "../se_sdk3/mp_sdk_audio.h"
#include "Karplus_strong_delay.h"

REGISTER_PLUGIN(Karplus_strong_delay, L"Karplus-Strong Delay");

Karplus_strong_delay::Karplus_strong_delay(IMpUnknown* host)
    : MpBase(host)
{
    initializePin(pinInput);
    initializePin(pinPitch);
    initializePin(pinFeedback);
    initializePin(pinOutput);
}

int32_t MP_STDCALL Karplus_strong_delay::open()
{
    MpBase::open();

    delayLine.init(this->getSampleRate(), MAX_DELAY_MS);
    delayLine.setDelayMs(INITIAL_DELAY_MS);
    delayLine.setDryFraction(INITIAL_DRY_FRACTION);
    delayLine.setFeedback(INITIAL_FEEDBACK_FRACTION);

    SET_PROCESS(&Karplus_strong_delay::subProcess);
    return gmpi::MP_OK;
}

void Karplus_strong_delay::subProcess(int bufferOffset, int sampleFrames)
{
    // get pointers to in/output buffers.
	float* pInput  = bufferOffset + pinInput.getBuffer();
	float* pPitch  = bufferOffset + pinPitch.getBuffer();
    float* pFeedback = bufferOffset + pinFeedback.getBuffer();
    float* pOutput = bufferOffset + pinOutput.getBuffer();

    for (int s = sampleFrames; s > 0; --s)
    {
        double pitchVolts = 10.0 * *pPitch++;
        delayLine.setDelayMs(1000.0 / (440.0 * pow(2.0, pitchVolts - 5.0)));
        delayLine.setFeedback(*pFeedback++);
        *pOutput++ = delayLine.push(*pInput++);
    }
}

void Karplus_strong_delay::onSetPins(void)
{
    // Check which pins are updated.
    if (pinInput.isStreaming())
    {
    }
    if (pinPitch.isStreaming())
    {
    }
    if (pinFeedback.isStreaming())
    {
    }

    // Set state of output audio pins.
    pinOutput.setStreaming(true);

    // Set processing method.
    SET_PROCESS(&Karplus_strong_delay::subProcess);

    // Set sleep mode (optional).
    // setSleep(false);
}
