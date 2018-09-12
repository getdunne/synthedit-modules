#include "spPhaser.h"
#include "TRACE.h"

REGISTER_PLUGIN( spPhaser, L"Soundpipe Phaser" );

spPhaser::spPhaser(IMpUnknown* host)
    : sp(0)
    , MpBase(host)
{
	// Register pins.
	initializePin(0, pinInputL);
    initializePin(1, pinInputR);

	initializePin(2, pinMaxNotch1Freq);
    initializePin(3, pinMinNotch1Freq);
    initializePin(4, pinNotchWidth);
    initializePin(5, pinNotchFreq);
    initializePin(6, pinVibratoMode);
    initializePin(7, pinDepth);
    initializePin(8, pinFeedback);
    initializePin(9, pinInvert);
    initializePin(10, pinLevel);
    initializePin(11, pinLFO_BPM);

    initializePin(12, pinOutputL);
    initializePin(13, pinOutputR);
}

int32_t MP_STDCALL spPhaser::open()
{
    MpBase::open();
    sp_create(&sp);
    sp_phaser_create(&phaser);
    sp_phaser_init(sp, phaser);

    SET_PROCESS(&spPhaser::subProcess);
    return gmpi::MP_OK;
}

spPhaser::~spPhaser()
{
    if (sp)
    {
        sp_destroy(&sp);
        sp_phaser_destroy(&phaser);
    }
}

// Process audio.
void spPhaser::subProcess( int bufferOffset, int sampleFrames )
{
	// assign pointers to your in/output buffers. Each buffer is an array of float samples.
	float* pInputL  = bufferOffset + pinInputL.getBuffer();
	float* pInputR  = bufferOffset + pinInputR.getBuffer();

	float* pOutputL  = bufferOffset + pinOutputL.getBuffer();
	float* pOutputR  = bufferOffset + pinOutputR.getBuffer();

    while (sampleFrames-- > 0)
	//for (int s = sampleFrames; s > 0; --s)
	{
        sp_phaser_compute(sp, phaser, pInputL++, pInputR++, pOutputL++, pOutputR++);
    }
}

// One or more inputs updated.  Check pin update flags to determin which ones.
void spPhaser::onSetPins(void)
{
	/*
	// LEVEL 1 - Simplest way to handle streaming status...
	// Do nothing. That's it.
	*/

#if 1

	// LEVEL 2 - Determine if output is silent or active, then notify downstream modules.
	//           Downstream modules can then 'sleep' (save CPU) when processing silence.

	// If either input is active, output will be active. ( "||" means "or" ).
	bool OutputIsActive = pinInputL.isStreaming() || pinInputR.isStreaming();

	// Exception...
	// If either input zero, output is silent.
	if (!pinInputL.isStreaming() && pinInputL == 0.0f)
	{
		OutputIsActive = false;
	}

	if (!pinInputR.isStreaming() && pinInputR == 0.0f)
	{
		OutputIsActive = false;
	}

	// Transmit new output state to modules 'downstream'.
	pinOutputL.setStreaming(OutputIsActive);
    pinOutputR.setStreaming(OutputIsActive);

    if (pinMaxNotch1Freq.isUpdated())
    {
        *(phaser->MaxNotch1Freq) = pinMaxNotch1Freq;
    }
    if (pinMinNotch1Freq.isUpdated())
    {
        *(phaser->MinNotch1Freq) = pinMinNotch1Freq;
    }
    if (pinNotchWidth.isUpdated())
    {
        *(phaser->Notch_width) = pinNotchWidth;
    }
    if (pinNotchFreq.isUpdated())
    {
        *(phaser->NotchFreq) = pinNotchFreq;
    }
    if (pinVibratoMode.isUpdated())
    {
        *(phaser->VibratoMode) = pinVibratoMode;
    }
    if (pinDepth.isUpdated())
    {
        *(phaser->depth) = pinDepth;
    }
    if (pinFeedback.isUpdated())
    {
        *(phaser->feedback_gain) = pinFeedback;
    }
    if (pinInvert.isUpdated())
    {
        *(phaser->invert) = pinInvert;
    }
    if (pinLevel.isUpdated())
    {
        *(phaser->level) = pinLevel;
    }
    if (pinLFO_BPM.isUpdated())
    {
        *(phaser->lfobpm) = pinLFO_BPM;
    }

	// Choose which function is used to process audio.
	// You can have one processing method, or several variations (each specialized for a certain condition).
	// For this example only one processing function needed.
	SET_PROCESS( &spPhaser::subProcess );

	// Normally module will sleep when no inputs or outputs are streaming,
	// however this module is an exception - when the volume on one input pin is zero, module can sleep
	// regardless of the other input.

	// control sleep mode manually.
	//setSleep(!OutputIsActive);
#endif
}

