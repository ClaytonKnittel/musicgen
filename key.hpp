#pragma once

#include "note.hpp"

class Key {
public:

    Key(float rootFreq, NoteName_T rootNote);

    /*
     * Generates the specified note justly tuned
     * to this key. Notes are chosen based on a
     * lookup table of the most sonorous intervals
     */
    Note_T generateNote(NoteName_T note, float duration, float volume);

    /*
     * Generates equal-tempered version
     */
    Note_T generateETNote(NoteName_T note, float duration, float volume);

private:

    /*
     * Frequency of the root of this key
     */
    float m_rootFreq;

    /*
     * Name of the root of this key
     */
    NoteName_T m_rootNote;

    int m_rootNoteAbsVal;
};
