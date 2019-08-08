#include <cstdio>
#include <cstdlib>
#include <string.h>

#include <cmath>

extern "C" {
    #include "wav.h"
}

#define PI 3.14159265358979324


int main(int argc, char *argv[]) {
    AudioFmt afmt;
    afmt.sample_rate = 44100;
    afmt.nSamples = 44100;
    afmt.nChannels = 1;
    afmt.nBitsPerSample = 16;

    short *data = (short*) malloc(sizeof(short) * afmt.nSamples);
    if (data == nullptr) {
        printf("Unable to initalize that\n");
        return 1;
    }

    for (size_t i = 0; i < afmt.nSamples; ++i) {
        data[i] = static_cast<short>(2000 * sin(0.1f + static_cast<float>(80.f * i * 2) * PI / afmt.sample_rate));
        data[i] += static_cast<short>(2000 * sin(1.f + static_cast<float>(160.f * i * 2) * PI / afmt.sample_rate));
        data[i] += static_cast<short>(2000 * sin(0.4f + static_cast<float>(240.f * i * 2) * PI / afmt.sample_rate));
        data[i] += static_cast<short>(2000 * sin(1.3f + static_cast<float>(320.f * i * 2) * PI / afmt.sample_rate));
    }

    audioWrite("file.wav", data, afmt);
    free(data);
    return 0;
}