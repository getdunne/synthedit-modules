#pragma once
#include "AdjustableDelayLine.hpp"

class KarplusStrongDelayLine : public AudioKitCore::AdjustableDelayLine
{
public:
    KarplusStrongDelayLine() : oldOutSample(0.0f), AdjustableDelayLine() {}
    ~KarplusStrongDelayLine() = default;

    inline float push(float sample)
    {
        if (!pBuffer) return sample;

        int ri = int(readIndex);
        float f = readIndex - ri;
        int rj = ri + 1; if (rj >= capacity) rj -= capacity;
        readIndex += 1.0f;
        if (readIndex >= capacity) readIndex -= capacity;

        float si = pBuffer[ri];
        float sj = pBuffer[rj];
        float outSample = (1.0f - f) * si + f * sj;

        // Here we add the 2-sample averaging filter required for Karplus-Strong
        pBuffer[writeIndex++] = sample + fbFraction * 0.5f * (oldOutSample + outSample);
        oldOutSample = outSample;
        if (writeIndex >= capacity) writeIndex = 0;

        return dryFraction * sample + outSample;
    }

protected:
    float oldOutSample;

};