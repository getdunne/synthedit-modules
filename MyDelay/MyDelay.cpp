#include "MyDelay.h"
#include "TRACE.h"

REGISTER_PLUGIN( MyDelay, L"My Delay" );

MyDelay::MyDelay( IMpUnknown* host ) : MpBase( host )
{
	// Register pins.
	initializePin(0, pinInput1);
	initializePin(1, pinDelaySec);
    initializePin(2, pinDryFraction);
    initializePin(3, pinFeedback);
    initializePin(4, pinOutput1 );
}

int32_t MP_STDCALL MyDelay::open()
{
    MpBase::open();

    delayLine.init(this->getSampleRate(), MAX_DELAY_MS);
    delayLine.setDelayMs(INITIAL_DELAY_MS);
    delayLine.setDryFraction(INITIAL_DRY_FRACTION);
    delayLine.setFeedback(INITIAL_FEEDBACK_FRACTION);

    SET_PROCESS(&MyDelay::subProcess);
    return gmpi::MP_OK;
}

// Process audio.
void MyDelay::subProcess( int bufferOffset, int sampleFrames )
{
	// assign pointers to your in/output buffers. Each buffer is an array of float samples.
	float* pIn1  = bufferOffset + pinInput1.getBuffer();
	float* pDelaySec  = bufferOffset + pinDelaySec.getBuffer();
    float* pDryFraction = bufferOffset + pinDryFraction.getBuffer();
    float* pFeedback = bufferOffset + pinFeedback.getBuffer();
    float* pOut1 = bufferOffset + pinOutput1.getBuffer();

    //TRACE("dly %f, dry %f, fb %f\n", *pDelaySec, *pDryFraction, *pFeedback);

	for( int s = sampleFrames; s > 0; --s ) // sampleFrames = how many samples to process (can vary). repeat (loop) that many times
	{
        delayLine.setDelayMs(1000.0 * *pDelaySec++);
        delayLine.setDryFraction(*pDryFraction++);
        delayLine.setFeedback(*pFeedback++);
        *pOut1++ = delayLine.push(*pIn1++);
    }
}

// One or more inputs updated.  Check pin update flags to determin which ones.
void MyDelay::onSetPins(void)
{
	/*
	// LEVEL 1 - Simplest way to handle streaming status...
	// Do nothing. That's it.
	*/

#if 0

	// LEVEL 2 - Determine if output is silent or active, then notify downstream modules.
	//           Downstream modules can then 'sleep' (save CPU) when processing silence.

	// If either input is active, output will be active. ( "||" means "or" ).
	bool OutputIsActive = pinInput1.isStreaming() || pinInput2.isStreaming();

	// Exception...
	// If either input zero, output is silent.
	if( !pinInput1.isStreaming() && pinInput1 == 0.0f )
	{
		OutputIsActive = false;
	}

	if( !pinInput2.isStreaming() && pinInput2 == 0.0f )
	{
		OutputIsActive = false;
	}

	// Transmit new output state to modules 'downstream'.
	pinOutput1.setStreaming( OutputIsActive );

	// Choose which function is used to process audio.
	// You can have one processing method, or several variations (each specialized for a certain condition).
	// For this example only one processing function needed.
	SET_PROCESS( &MyDelay::subProcess );

	// Normally module will sleep when no inputs or outputs are streaming,
	// however this module is an exception - when the volume on one input pin is zero, module can sleep
	// regardless of the other input.

	// control sleep mode manually.
	setSleep( !OutputIsActive );
#endif
}

