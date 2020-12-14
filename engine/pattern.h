#ifndef FYNEWAV_PATTERN
#define FYNEWAV_PATTERN
#include <vector>
#include <patternNote.h>

/**Pattern class, represents a Pattern in FyneWav
 * Attributes:
 *      - m_notes: Pattern's PatternNote list
 *      - m_size: Pattern's size (or length)
 *      - m_pos: Pattern's position from track start
 * Constructors:
 *      - Pattern(): Empty constructor
 *      - Pattern(notes): Constructor with notes
 *      - Pattern(notes, pos): Constructor with notes and position
 *      - Pattern(pos, size): Constructor with position and size
 *      - Pattern(notes, size): Constructor with notes and size
 *      - Pattern(notes, pos, size): Full constructor
 * 
 * Methodes:
 *      - tick(position): Looks for PatternNote to play
 *      - addPatternNote(note): Adds the PatternNote to m_notes
 *      - reset(): Reset all PatternNote's played state
 *      - getNoteAt(index): Returns the note at the index in m_notes
*/
class Pattern
{
public:
    /*Pattern's PatternNote list*/
    std::vector<PatternNote> m_notes;
    /*Pattern's size (or length) (in samples)*/
    unsigned int m_size;
    /*Pattern's position from track start (in samples)*/
    unsigned int m_pos;

    /*Empty constructor*/
    Pattern() : m_pos(0), m_size(stk::Stk::sampleRate()) {}
    /*Constructor with PatternNote list (m_pos=0, m_size=[maxNoteSize])*/
    Pattern(std::vector<PatternNote> notes) : m_pos(0)
    {
        m_notes = notes;
        unsigned int size = 0;
        for (auto i = notes.begin(); i < notes.end(); i++)
        {
            unsigned int noteLength = i->m_pos + i->m_note.m_length;
            if (noteLength > size)
                size = noteLength;
        }
        m_size = size;
    }
    /*Constructor with PatternNote list and position (m_size=[maxNoteSize])*/
    Pattern(std::vector<PatternNote> notes, unsigned int pos)
    {
        m_pos = pos;
        m_notes = notes;
        unsigned int size = 0;
        for (auto i = notes.begin(); i < notes.end(); i++)
        {
            unsigned int noteLength = i->m_pos + i->m_note.m_length;
            if (noteLength > size)
                size = noteLength;
        }
        m_size = size;
    }
    /*Constructor with position and size*/
    Pattern(unsigned int pos, unsigned int size)
    {
        m_pos = pos; m_size = size;
    }
    /*Constructor with PatternNote list and size (m_pos=0)*/
    Pattern(std::vector<PatternNote> notes, unsigned int size) : m_pos(0)
    {
        m_size = size; m_notes = notes;
    }
    /*Full constructor*/
    Pattern(std::vector<PatternNote> notes, unsigned int pos, unsigned int size)
    {
        m_notes = notes; m_pos = pos; m_size = size;
    }

    /*Looks for PatternNote to play*/
    void tick(unsigned int position) {
        for (auto i = m_notes.begin(); i < m_notes.end(); i++)
        {
            if (i->m_pos == position && !i->played)
            {
                i->played = true;
                i->m_vst->noteOn(i->m_note);
            }
        }
    }
    void reset() {
        for (auto i = m_notes.begin(); i < m_notes.end(); i++)
        {
            i->played = false;
        }
    }

    void addPatternNote(Note note, unsigned int position, Vst *vst) {
        m_notes.push_back(PatternNote(position, note, vst));
    }
    void addPatternNote(PatternNote pNote) {
        m_notes.push_back(pNote);
    }
    PatternNote* getNoteAt(unsigned short index) {
        PatternNote* pNote = &(*m_notes.begin() ) + index * sizeof(PatternNote);
        return pNote;
    }
    PatternNote* getNoteFrom(unsigned short position, unsigned short height) {
        PatternNote* pNote = nullptr;
        for (auto i = m_notes.begin(); i < m_notes.end(); i++)
        {
            if (i->m_pos == position && i->m_note.m_height == height) {
                pNote = &(*i);
                break;
            }
        }
        return pNote;
    }
    // TODO: getter-setter
};
#endif