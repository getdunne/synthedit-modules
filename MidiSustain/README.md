# MIDI Sustain

This SynthEdit Module uses a *AudioKitCore::SustainLogic* instance to interpret MIDI sustain pedal down/up events, suppressing note-off events while the pedal is down.

Many Synth VSTs built with SynthEdit didn't respond to MIDI sustain-pedal events at all. Inserting an instance of this module in series with the main MIDI input will fix this.

The SynthEdit project file *SustainDemo.se1* allows you to observe what this module does, using a MIDI Monitor.
