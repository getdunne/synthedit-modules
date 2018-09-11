#pragma once

#include "mp_sdk_audio.h"
#include "SustainPedalLogic.hpp"

class MidiSustain : public MpBase
{
public:
	MidiSustain( IMpUnknown* host );
	virtual void onMidiMessage(int pin, unsigned char* midiMessage, int size); // size < 4 for short msg, or > 4 for sysex

private:
	MidiInPin pinMIDIIn;
	MidiOutPin pinMIDIOut;

    AudioKitCore::SustainPedalLogic pedalLogic;
};
