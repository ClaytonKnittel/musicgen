#pragma once

#include <vector>
#include "note.hpp"


class Chord_T {
public:

    Chord_T(NoteName_T* notes,
            size_t numNotes);
    
    Chord_T(std::vector<NoteName_T> notes);

    Chord_T(std::vector<std::string> notes);

    NoteName_T operator[](size_t i);

    size_t size() const;

private:

    std::vector<NoteName_T> m_notes;
    size_t m_numNotes;
};
