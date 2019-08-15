
#include "SimpleSampler.hpp"
#include <random>
#include <cmath>

#define PI 3.14159265358979324

#define SAMPLE_T_MAX ((sample_t) (~(1 << (8 * sizeof(sample_t) - 1))))

SimpleSampler::SimpleSampler(int sample_rate):
    Sampler_T(sample_rate)
{
}


int SimpleSampler::sample(sample_t* dest, size_t size, float freq, float volume) const {
    float phase_shift = PI * static_cast<float>(rand()) / RAND_MAX;
    float mag = SAMPLE_T_MAX * volume;
    for (size_t i = 0; i < size; ++i) {
#define WIDTH 2000
        float mul = 1.f;
        if (i < WIDTH)
            mul = static_cast<float>(i) / WIDTH;
        else if (i > size - WIDTH)
            mul = static_cast<float>(size - i) / WIDTH;
        dest[i] += static_cast<sample_t>(mul * mag * sin(phase_shift + freq * static_cast<float>(i) * 2 * PI / m_sampleRate));
    }
    return 0;
}
