#ifndef FYNEWAV_PATTERNNOTE
#define FYNEWAV_PATTERNNOTE
#include <note.h>
#include <vst.h>

/**PatternNote class, represents a Pattern Note in FyneWav
 * Attributes:
 *      - m_pos: PatternNote's position from his Pattern's start Position
 *      - m_note: PatternNote's note class
 *      - m_vst: PatternNote's vst pointer
 * Constructors:
 *      - PatternNote(): Empty constructor
 *      - PatternNote(note): Constructor specifying note class
 *      - PatternNote(note, vst): Constructor with note and vst
 *      - PatternNote(pos, note): Constructor with position and note
 *      - PatternNote(pos, note, vst): Full constructor
 * 
 * Methodes:
 *      - play(): Asks PatternNote's m_vst to play m_note
 *      - changePosTo(position): Changes PatternNote's position to the new one
 *      - changePosBy(amount): Changes PatternNote's position by the given amount
 *      - setVstTo(vst): Set PatternNote's m_vst to the new one
 *      - setNoteTo(note): Set PatternNote's m_note to the new one
*/
class PatternNote
{
public:
    /*PatternNote's position from his Pattern's start position (in samples)*/
    unsigned int m_pos;
    /*PatternNote's played state*/
    bool played;
    /*PatternNote's playing vst pointer*/
    Vst *m_vst;
    /*PattenNote's note class*/
    Note m_note;
    /*Empty constructor (m_pos=0, played=false, m_note=Note(), m_vst=null)*/
    PatternNote() : m_pos(0), played(false) {};
    /*Note constructor (m_pos=0, played=false, m_note=note, m_vst=null)*/
    PatternNote(Note note) : m_pos(0), played(false) { m_note = note; };
    /*Note and vst constructor (m_pos=0, played=false, m_note=note, m_vst=vst)*/
    PatternNote(Note note, Vst *vst) : m_pos(0), played(false)
    {
        m_note = note;
        m_vst = vst;
    };
    /*Pos and note constructor (m_pos=pos, m_note=note, m_vst=null)*/
    PatternNote(unsigned int pos, Note note)
    {
        m_note = note;
        m_pos = pos;
    };
    /*Full constructor (m_pos=pos, m_note=note, m_vst=vst)*/
    PatternNote(unsigned int pos, Note note, Vst *vst)
    {
        m_note = note;
        m_pos = pos;
        m_vst = vst;
    };

    /*Asks PatternNote's m_vst to play m_note*/
    void play()
    {
        m_vst->noteOn(m_note);
    }
    /*Changes PatternNote's position to the new position*/
    void changePosTo(unsigned int position)
    {
        m_pos = position;
    }
    /*Changes PatternNote's position by the given amount*/
    void changePosBy(int amount)
    {
        m_pos += amount;
    }
    /*Set PatternNote's m_vst to the new one*/
    void setVstTo(Vst *vst)
    {
        m_vst = vst;
    }
    /*Set PatternNote's m_note to the new one*/
    void setNoteTo(Note note)
    {
        m_note = note;
    }
};
#endif