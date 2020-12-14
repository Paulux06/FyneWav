#ifndef FYNEWAV_VST
#define FYNEWAV_VST
#include <vector>
#include <generator.h>

/*Vst class, represents a vst in FyneWav
 * Attributes:
 *      - m_notes: current notes played by the vst.
 *      - m_pitch: current pitch of the vst.
 *      - m_volume: current volume of the vst.
 *      - m_generator: sound generator of the vst.
 * Constructors:
 *      - Vst(): Empty constructor.
 *      - Vst(generator): Generator constructor.
 *      - Vst(generator, pitch): Full constructor.
 * Methodes:
 *      - tick(): return new generated sample by m_generator from notes.
 *      - noteOn(note): adds the new Note to m_notes to play it.
 *      - clearNotes(): removes all the current notes played.
*/
class Vst
{
public:
    /*Vst's current played generators (or notes).*/
    std::vector<Note> m_list;
    /*Vst's current volume. (max=65535)*/
    unsigned short m_volume;
    /*Vst's sound generator.*/
    Generator m_generator;

    /*Empty constructor. (m_volume=65535, generator=default generator)*/
    Vst() : m_volume(65535) { m_generator = Generator(); }
    /*Generator constructor. (m_volume=1)*/
    Vst(Generator generator) : m_volume(1) { m_generator = generator; }
    /*Full constructor.*/
    Vst(Generator generator, unsigned short volume)
    {
        m_volume = volume;
        m_generator = generator;
    }

    /*adds a new Note from height, velocity, length, pan to current played notes list.*/
    void noteOn(unsigned short height, unsigned short velocity,
                unsigned int length, short pan)
    {
        Note n = Note(height, velocity, length, pan);
        m_list.push_back(n);
        std::cout << "a vst is playing a new note" << std::endl;
    }
    /*adds the new Note to current played notes list.*/
    void noteOn(Note note)
    {
        m_list.push_back(Note(note));
    }
    /*removes all the current notes played.*/
    void clearNotes()
    {
        m_list.clear();
    }
    /*return new generated sample by m_generator from notes.*/
    StereoSample tick()
    {
        StereoSample sample(0, 0);
        double nbrNote = m_list.size();
        for (auto i = m_list.begin(); i < m_list.end(); i++)
        {
            StereoSample out = m_generator.tick(i);
            out /= nbrNote;
            sample += out;
            if (i->m_progress == i->m_length)
                m_list.erase(i);
        }
        sample *= (m_volume / 65535.0);
        return sample;
    }
};
#endif