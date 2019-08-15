
#include "key.hpp"
#include <cmath>
#include <string.h>
#include <cstdarg>

extern "C" {
    #include "musmath.h"
}


struct Ratio_T {

    Ratio_T(short num, short denom):
            denom(denom), num(num)
    {
        fraction = num / denom;
    }

    short denom, num;
    float fraction;
};

// const static RatioChoice_T pRatios[12] {
//     /*
//      *
//      */
    
// };


const static float ratios[12] {
    1.f,        // unison/octave
    1.066667f,  // semitone
    1.125f,     // major second
    1.2f,       // minor third
    1.25f,      // major third
    1.333333f,  // perfect fourth
    1.4,        // lesser septimal tritone
    1.5f,       // perfect fifth
    1.6f,       // minor sixth
    1.666666f,  // major sixth
    1.833333f,  // minor seventh
    1.875f      // major seventh
};

Key::Key(float rootFreq, NoteName_T rootNote):
        m_rootFreq(rootFreq),
        m_rootNote(rootNote),
        m_rootNoteAbsVal(rootNote.getAbsoluteValue())
{
}

Note_T Key::generateNote(NoteName_T note, float duration, float volume) {
    int absval = note.getAbsoluteValue();
    int offset = absval - m_rootNoteAbsVal;
    float scale = 1.f;
    while (offset > 11) {
        scale *= 2.f;
        offset -= 12;
    }
    while (offset < 0) {
        scale /= 2.f;
        offset += 12;
    }
    scale *= ratios[offset];
    float freq = scale * m_rootFreq;
    return Note_T(freq, duration, volume);
}

Note_T Key::generateETNote(NoteName_T note, float duration, float volume) {
    int absval = note.getAbsoluteValue();
    int offset = absval - m_rootNoteAbsVal;
    float scale = 1.f;
    while (offset > 11) {
        scale *= 2.f;
        offset -= 12;
    }
    while (offset < 0) {
        scale /= 2.f;
        offset += 12;
    }
    scale *= pow(2, static_cast<float>(offset) / 12.f);
    float freq = scale * m_rootFreq;
    return Note_T(freq, duration, volume);
}
