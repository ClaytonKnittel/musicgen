#ifndef C_WAV_H /* Include guard */
#define C_WAV_H

#include <stdio.h>

#define uint unsigned int


// Standard sample rates
#define WAVE_SAMPLE_RATE_8000   8000
#define WAVE_SAMPLE_RATE_44100  44100
#define WAVE_SAMPLE_RATE_96000  96000



typedef struct AudioFmt_T {
    // total number of samples in audio (per channel)
    size_t nSamples;

    // rate at which samples were measured
    uint sample_rate;

    // number of independent audio channels
    uint nChannels;

    // number of bits per sample per channel (usually 8 or 16)
    uint nBitsPerSample;
} AudioFmt;

int audioWrite(const char* file, const short* audioData, AudioFmt afmt);


#endif /* Include guard */
