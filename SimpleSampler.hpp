#pragma once

#include "sampler.hpp"


class SimpleSampler : public Sampler_T {
public:

    SimpleSampler(int sample_rate);

    /*
     * Uses a basic sine wave model for sound, with a
     * random phase shift
     */
    virtual int sample(sample_t* dest, size_t size, float freq, float volume) const;

};
