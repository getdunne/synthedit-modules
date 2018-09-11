#include "./MidiSustain.h"
#include <climits>

REGISTER_PLUGIN ( MidiSustain, L"MIDI Sustain" );

#define NOTE_OFF    0x80
#define NOTE_ON     0x90
#define MIDI_CC     0xB0
#define CC_DAMPER   0x40


MidiSustain::MidiSustain(IMpUnknown* host)
    : MpBase(host)
{
	// Register pins.
	initializePin( 0, pinMIDIIn );
	initializePin( 1, pinMIDIOut );

}

void MidiSustain::onMidiMessage(int pin, unsigned char* midiMessage, int size)
{
	int stat,b2,b3,midiChannel;// 3 bytes of MIDI message

	midiChannel = midiMessage[0] & 0x0f;

	stat = midiMessage[0] & 0xf0;
	b2 = midiMessage[1];
	b3 = midiMessage[2];

	// Note offs can be note_on vel=0
	if (b3 == 0 && stat == NOTE_ON)
	{
		stat = NOTE_OFF;
	}

	switch (stat)
	{
	case NOTE_ON:
        if (pedalLogic.keyDownAction(b2))
        {
            // note should stop before playing again
            midiMessage[0] = NOTE_OFF | midiChannel;
            pinMIDIOut.send(midiMessage, size, blockPosition());
            midiMessage[0] = NOTE_ON | midiChannel;
        }
        break;
	case NOTE_OFF:
        if (!pedalLogic.keyUpAction(b2))
        {
            // note should NOT stop
            return;
        }
        break;

    case MIDI_CC:
        if (b2 == CC_DAMPER)
        {
            if (b3 > 63)
            {
                // pedal depressed
                pedalLogic.pedalDown();
            }
            else
            {
                // pedal released
                pedalLogic.pedalUp();

                for (int nn = 0; nn < AudioKitCore::kMidiNoteNumbers; nn++)
                {
                    if (pedalLogic.isNoteSustaining(nn))
                    {
                        midiMessage[0] = NOTE_OFF | midiChannel;
                        midiMessage[1] = nn;
                        midiMessage[2] = 0;
                        pinMIDIOut.send(midiMessage, 3, blockPosition());
                    }
                }
                pedalLogic.init();
            }
            // don't pass on damper pedal messages
            return;
        }

	default:
        // all other cases are just passed through
		break;
	}

    // send original MIDI message and return
    pinMIDIOut.send(midiMessage, size, blockPosition());
}
