#pragma once

#include "sampler.hpp"
#include <string>

class NoteName_T {
    /*
     * Respresents the abstract idea of a note. It
     * is not tied to a specific freqneucy to be
     * played at, but rather will later on be justly
     * tuned to the notes around it
     */
public:

    enum Accidental {
        NATURAL,
        SHARP,
        FLAT
    };

    NoteName_T(const char* name);
    NoteName_T(const std::string &name);

    /*
     * Creates the lowest note of the given pitch above
     * the note base, thus note should not specify its
     * octave
     */
    static NoteName_T above(NoteName_T base, std::string note);

    char getLetter() const;
    Accidental getAccidental() const;
    int getOctave() const;

    /* returns a value from 21-108, where A0
     * is mapped to 21 and C8 is 108, with all
     * other notes in between, separated by
     * semitones
     */
    int getAbsoluteValue() const;

    std::string getName() const;

    bool operator>(const NoteName_T &n) const;
    bool operator<(const NoteName_T &n) const;
    bool operator>=(const NoteName_T &n) const;
    bool operator<=(const NoteName_T &n) const;
    bool operator==(const NoteName_T &n) const;
    bool operator!=(const NoteName_T &n) const;

private:
    /*
     * Note data is stored compactly in a single byte.
     * As there are 7 possible notes, three possible
     * accidentals (flat, sharp, natural), and 8 possible
     * octaves (0-7) (C8 is stored as C0 for compactness),
     * we only need 8 bits of information to encode a note.
     * 
     * +-------------+------------+-------------+
     * |             |            |             |
     * |  Note name  | Accidental |   Octave    |
     * |  (3 bits)   |  (2 bits)  |   (3 bits)  |
     * |             |            |             |
     * +-------------+------------+-------------+
     * 
     * 
     */
    unsigned char m_data;
};


class Note_T {
    /*
     * Represents a real physical note being played
     * at some specific freqneucy for some length in
     * time
     */
public:

    Note_T(float baseFreq,
           float duration,
           float volume);

    /*
     * Plays the note to the given destination buffer
     * 
     * The sampler is what is used to generate the
     * audio signal when requested externally. The
     * base frequency is to be passed directly to it
     */
    int play(sample_t* dest, const Sampler_T *sampler);

private:
    /*
     * Base frequency is given in Hz. This value
     * may either be used to generate a sound wave
     * of the given frequency, or used to sample
     * the given midi input
     */
    float m_baseFreq;

    /*
     * Duration is given in terms of measures.
     * e.g. a quarter note would have duration 0.25f
     */
    float m_duration;

    /*
     * Represents how loud this note is, on a scale
     * from 0.f - 1.f
     */
    float m_volume;

};

