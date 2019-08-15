
#include "note.hpp"

#define NATURAL 0x00
#define SHARP   0x01
#define FLAT    0x02

#define NOTE_IN_RANGE(letter, accidental, octave) \
    (!((octave == 0 && (letter >= 'C' || (letter == 'A' && accidental == FLAT))) || \
     (octave == 8 && (letter != 'C' || accidental == SHARP)) ||                     \
     (octave > 8 || octave < 0)))

const static char* acc_strs[3] = {"", "#", "b"};

#define accidental_to_string(accidental) \
    (acc_strs[static_cast<int>(accidental)])

NoteName_T::NoteName_T(const char* name) {
    char letter = *(name++);
#if DEBUG
    if ((letter < 'a' || letter > 'g') &&
        (letter < 'A' || letter > 'G')) {
        fprintf(stderr, "letter %c is not a valid note name\n", letter);
        return;
    }
#endif
    char octave = *(name++);
    char accidental;
#if DEBUG
    if (octave == '\0') {
        fprintf(stderr, "No octave specified to note %c\n", letter);
        return;
    }
#endif
    if (octave == '#' || octave == 'b') {
        accidental = octave;
        octave = *(name++);
    }
    else {
        accidental = ' ';
    }
#if DEBUG
    if (octave == '\0') {
        fprintf(stderr, "No octave specified to note %c%c\n", letter, accidental);
    }
    if (*name != '\0') {
        fprintf(stderr, "Note has invalid length\n");
        return;
    }
#endif
    if (letter >= 'a' && letter <= 'g') {
        letter += 'A' - 'a';
    }
    octave -= '0';
#if DEBUG
    char acci = (accidental == ' ' ? NATURAL :
                 accidental == '#' ? SHARP :
                 FLAT);
    m_data |= octave;
    if (!NOTE_IN_RANGE(letter, acci, octave)) {
        if (acci == NATURAL)
            fprintf(stderr, "Note %c%d is outside range\n", letter, octave);
        else
            fprintf(stderr, "Note %c%c%d is outside range\n", letter, accidental, octave);
        return;
    }
#endif
    if (octave == 8 && letter == 'C')
        octave = 0;
    m_data = (letter - 'A') << 5;
    m_data |= (accidental == ' ' ? NATURAL << 3 :
               accidental == '#' ? SHARP << 3 :
               FLAT << 3);
    m_data |= octave;
}

NoteName_T::NoteName_T(const std::string &name):
    NoteName_T(name.c_str())
{
}

// TODO: Make this more efficient
NoteName_T NoteName_T::above(NoteName_T base, std::string note) {
    int baseVal = base.getAbsoluteValue();
    note += '3';
    NoteName_T ret(note.c_str());
    while (baseVal < ret.getAbsoluteValue()) {
        ret.m_data--;
    }
    while (baseVal >= ret.getAbsoluteValue()) {
        ret.m_data++;
    }
    return ret;
}

char NoteName_T::getLetter() const {
    char val = (m_data >> 5) + 'A';
#if DEBUG
    if ((m_data >> 5) > ('G' - 'A')) {
        fprintf(stderr, "m_data corrupted in note: note letter has invalid value %c\n", val);
    }
#endif
    return val;
}

NoteName_T::Accidental NoteName_T::getAccidental() const {
    int acc = (m_data >> 3) & 0x03;
#if DEBUG
    if (acc == 0x03) {
        fprintf(stderr, "m_data corrupted in note: accidental has invalid value %d\n", acc);
    }
#endif
    return static_cast<NoteName_T::Accidental>(acc);
}

int NoteName_T::getOctave() const {
    int val = m_data & 0x07;
    if (val == 0 && getLetter() == 'C')
        val = 8;
    return val;
}

int NoteName_T::getAbsoluteValue() const {
    const static int offsets[7] = {21, 23, 12, 14, 16, 17, 19};
    int offset = offsets[m_data >> 5];
    offset += 12 * getOctave();
    switch(getAccidental()) {
    case NATURAL:
        break;
    case SHARP:
        offset++;
        break;
    case FLAT:
        offset--;
    }
    return offset;
}

std::string NoteName_T::getName() const {
    std::string ret;
    char letter = getLetter();
    Accidental acc = getAccidental();
    char octave = getOctave();
#if DEBUG
    if (!NOTE_IN_RANGE(letter, static_cast<int>(acc), octave)) {
        fprintf(stderr, "Note %c%s%c not in valid range\n", letter, accidental_to_string(acc), octave);
        return "";
    }
#endif
    ret += letter;
    ret += accidental_to_string(acc);
    ret += (octave + '0');
    return ret;
}


#define NOTENAME_COMP_OP(op) \
    bool NoteName_T::operator op(const NoteName_T &n) const { \
        return getAbsoluteValue() op n.getAbsoluteValue();    \
    }

NOTENAME_COMP_OP(>)
NOTENAME_COMP_OP(<)
NOTENAME_COMP_OP(>=)
NOTENAME_COMP_OP(<=)
NOTENAME_COMP_OP(==)
NOTENAME_COMP_OP(!=)

#undef NOTENAME_COMP_OP

Note_T::Note_T(float baseFreq,
               float duration,
               float volume):
            m_baseFreq(baseFreq),
            m_duration(duration),
            m_volume(volume)
{
}


int Note_T::play(sample_t* dest, const Sampler_T *sampler) {
    size_t len = static_cast<size_t>(m_duration * sampler->sample_rate());
    return sampler->sample(dest, len, m_baseFreq, m_volume);
}
