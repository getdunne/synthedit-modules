# Karplus-Strong Delay

The [Karplus-Strong string synthesis](https://en.wikipedia.org/wiki/Karplus%E2%80%93Strong_string_synthesis) method makes use of a filtered delay-line, whose length is always tuned to correspond to a single cycle of the modeled string's fundamental frequency.

This SynthEdit Module uses a variable-length 1-tap digital delay to provide the tuned delay-line for the Karplus-Strong method, according to a standard *pitch* input which is scaled according to the standard SynthEdit "1 volt per octave" definition. (Note the actual input signal, from the *pitch* output of, say, a keyboard module, will be in the range 0.0 to 1.0, and must be scaled by a factor of 10 to yield 1 unit per octave. The mid-range value 0.5, which corresponds to 5 volts, equates to 440 Hz by definition.)

Following the original [Karplus-Strong algorithm definition](https://ccrma.stanford.edu/~jos/pasp/Karplus_Strong_Algorithm.html), this module adds a simple two-sample moving-average filter to the feedback path of the delay-line. More sophisticated filters could be substituted for different sounds.

