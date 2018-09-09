#include "sem_main.h"
#include "TRACE.h"

REGISTER_PLUGIN( $safeprojectname$, L"KS Delay" );

$safeprojectname$::$safeprojectname$( IMpUnknown* host ) : MpBase( host )
{
	// Register pins.
	initializePin(0, pinInput);
    initializePin(1, pinOutput);
}

int32_t MP_STDCALL $safeprojectname$::open()
{
    MpBase::open();

    SET_PROCESS(&$safeprojectname$::subProcess);
    return gmpi::MP_OK;
}

// Process audio.
void $safeprojectname$::subProcess( int bufferOffset, int sampleFrames )
{
	float* pInput  = bufferOffset + pinInput.getBuffer();
    float* pOutput = bufferOffset + pinOutput.getBuffer();

	for( int s = sampleFrames; s > 0; --s )
	{
        *pOutput++ = *pInput++;
    }
}

// One or more inputs updated.  Check pin update flags to determine which ones.
void $safeprojectname$::onSetPins(void)
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
	SET_PROCESS( &$safeprojectname$::subProcess );

	// Normally module will sleep when no inputs or outputs are streaming,
	// however this module is an exception - when the volume on one input pin is zero, module can sleep
	// regardless of the other input.

	// control sleep mode manually.
	setSleep( !OutputIsActive );
#endif
}

