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
class Vst {
    public:
        /*Vst's current played notes.*/
        std::vector<Note> m_notes;
        /*Vst's current volume. (max=65535)*/
        unsigned short m_volume;
        /*Vst's sound generator.*/
        Generator m_generator;

        /*Empty constructor. (m_volume=1, generator=empty generator)*/
        Vst(): m_volume(1) {m_generator = Generator();}
        /*Generator constructor. (m_volume=1)*/
        Vst(Generator generator): m_volume(1) {m_generator = generator;}
        /*Full constructor.*/
        Vst(Generator generator, unsigned short volume) {m_volume = volume; m_generator = generator;}

        /*adds a new Note from height, velocity, length, pan to current played notes list.*/
        void noteOn(unsigned short height, unsigned short velocity,
                    unsigned int length, short pan) {
            Note n = Note(height, velocity, length, pan);
            m_notes.push_back(n);
        }
        /*adds the new Note to current played notes list.*/
        void noteOn(Note note) {
            m_notes.push_back(note);
        }
        /*removes all the current notes played.*/
        void clearNotes() {
            m_notes.clear();
        }
        /*return new generated sample by m_generator from notes.*/
        StereoSample tick() {
            StereoSample sample(0, 0);
            for (auto i = m_notes.begin(); i < m_notes.end(); i++)
            {
                sample += m_generator.tick(*i);
                i->m_length--;
                if (i->m_length == 0) m_notes.erase(i);
                
            }
            return sample;
        }
};