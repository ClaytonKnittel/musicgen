#pragma once

typedef unsigned long size_t;
typedef short sample_t;

class Sampler_T {

public:

    explicit Sampler_T(int sample_rate):
        m_sampleRate(sample_rate)
    {
    }

    int sample_rate() const {
        return m_sampleRate;
    }

    /*
     * Sample a note at frequency freq for the given
     * number of sample points, writing to dest
     */
    virtual int sample(sample_t* dest, size_t size, float freq, float volume) const = 0;

protected:

    /*
     * Sample rate of audio file being written to
     */
    int m_sampleRate;

};
