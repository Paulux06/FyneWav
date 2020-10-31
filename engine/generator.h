#include <math.h>
#include <note.h>
#include <stereosample.h>
#include <Stk.h>

/*Generator class, represents a sound generator in FyneWav.
 * Attributes:
 *      - None.
 * Constructors:
 *      - Generator(): Empty constructor.
 * Methodes:
 *      - tick(note): Produces the generator sound based on note's attributes.
*/
class Generator {
    public:
        /*count variable*/
        long double i;
        /*Empty constructor.*/
        Generator() {}
        /*Produces the generator sound based on note's attributes.*/
        StereoSample tick(Note note) {
            double wave = sin(i/stk::Stk::sampleRate()) * (note.m_velocity/65535.0);
            i += 6.2831853 * note.m_height;
            StereoSample out(wave* abs(note.m_pan - 32767) / 65535.0, wave * abs(note.m_pan + 32767) / 65535.0);
            return out;
        }
};