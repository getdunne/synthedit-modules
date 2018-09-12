#pragma once
#include "mp_sdk_audio.h"
extern "C" {
#include "soundpipe.h"
}

class spPhaser: public MpBase
{
public:
	spPhaser(IMpUnknown* host);
    virtual ~spPhaser();
    int32_t MP_STDCALL open() override;
	void subProcess(int bufferOffset, int sampleFrames);
	virtual void onSetPins(void);

private:
	AudioInPin pinInputL, pinInputR;
    FloatInPin pinMaxNotch1Freq;
    FloatInPin pinMinNotch1Freq;
    FloatInPin pinNotchWidth;
    FloatInPin pinNotchFreq;
    FloatInPin pinVibratoMode;
    FloatInPin pinDepth;
    FloatInPin pinFeedback;
    FloatInPin pinInvert;
    FloatInPin pinLevel;
    FloatInPin pinLFO_BPM;
	AudioOutPin pinOutputL, pinOutputR;

    sp_data *sp;
    sp_phaser *phaser;
};
