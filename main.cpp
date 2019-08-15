#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>

#include <cmath>

#include "note.hpp"
#include "chord.hpp"
#include "key.hpp"
#include "SimpleSampler.hpp"

extern "C" {
    #include "musmath.h"
    #include "wav.h"
}

#define PI 3.14159265358979324


int main(int argc, char *argv[]) {
    int res[15];

    cf(res, PI, 15);

    for (int i = 0; i < 15; ++i)
        printf("%d\n", res[i]);

    /*
    AudioFmt afmt;
    afmt.sample_rate = WAVE_SAMPLE_RATE_44100;
    afmt.nSamples = 10 * afmt.sample_rate;
    afmt.nChannels = 1;
    afmt.nBitsPerSample = 16;

    short *data = (short*) calloc(sizeof(short) * afmt.nSamples, 1);
    if (data == nullptr) {
        printf("Unable to initalize that\n");
        return 1;
    }

    std::vector<Key> keys = {
        Key(264.f, "C4"),
        //Key(77.5f, "Eb1"),
        Key(77.5f, "Eb1")
    };

    // std::vector<Chord_T> chords = {
    //     std::vector<std::string>{"C#3", "E#", "B", "D", "E", "G", "A", "B"},
    //     std::vector<std::string>{"F#2", "D#", "B", "C#", "F#", "G#", "A#", "B"},
    // };
    
    // std::vector<Chord_T> chords = {
    //     std::vector<std::string>{"F#1", "C#", "A", "B", "E", "F#", "G#", "B", "Eb"},
    //     std::vector<std::string>{"B1", "A", "Eb", "F", "G", "Bb", "D"}
    // };

    // std::vector<Chord_T> chords = {
    //     std::vector<std::string>{"C4", "A"}
    // };

    // for (int h = 0; h < chords.size(); ++h) {
    //     Chord_T &note = chords[h];
    //     for (int i = 0; i < note.size(); i++) {
    //         Note_T notef = keys[h].generateNote(note[i], 2.f, .04f + static_cast<float>(i) * .02f);
    //         printf("%f\n", *((float*) &notef) / 77.5f);
    //         SimpleSampler simple_sampler(afmt.sample_rate);
    //         notef.play(data + (h * 44100), &simple_sampler);
    //     }
    //     printf("\n");
    // }

    float phase_shift = PI * static_cast<float>(rand()) / RAND_MAX;
    float mag = ((sample_t) (~(1 << (8 * sizeof(sample_t) - 1)))) * .3f;
    for (size_t i = 0; i < afmt.nSamples; ++i) {
#define WIDTH 2000
        float mul = 1.f;
        if (i < WIDTH)
            mul = static_cast<float>(i) / WIDTH;
        else if (i > afmt.nSamples - WIDTH)
            mul = static_cast<float>(afmt.nSamples - i) / WIDTH;
        
        data[i] = static_cast<sample_t>(mul * mag * sin(phase_shift + 440.f * static_cast<float>(i) * 2 * PI / afmt.sample_rate));
        data[i] += static_cast<sample_t>(mul * mag * sin(phase_shift + 440.f * static_cast<float>(i + i * i / 882000.f) * 2 * PI / afmt.sample_rate));
    }

    

    audioWrite("file.wav", data, afmt);
    free(data);*/
    return 0;
}