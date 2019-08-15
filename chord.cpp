
#include "chord.hpp"


Chord_T::Chord_T(NoteName_T* notes,
                 size_t numNotes) {
    m_notes.reserve(numNotes);
    for (size_t i = 0; i < numNotes; ++i) {
        m_notes.push_back(notes[i]);
    }
}

Chord_T::Chord_T(std::vector<NoteName_T> notes):
            m_notes(notes) {
    
}


Chord_T::Chord_T(std::vector<std::string> notes) {
    m_notes.reserve(notes.size());
    m_notes.push_back(notes[0]);
    for (size_t i = 1; i < notes.size(); ++i)
        m_notes.push_back(NoteName_T::above(m_notes[i - 1], notes[i]));
}


NoteName_T Chord_T::operator[](size_t i) {
    return m_notes[i];
}


size_t Chord_T::size() const {
    return m_notes.size();
}

