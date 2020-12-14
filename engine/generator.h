#ifndef FYNEWAV_GENERATOR
#define FYNEWAV_GENERATOR
#include <fstream>
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
class Generator
{
public:
    int type;
    /*Empty constructor.*/
    Generator(): type(0) {}
    /*Produces the generator sound based on note's attributes. (and changes note progress and length)*/
    StereoSample tick(std::vector<Note>::iterator note)
    {
        double wave;
        switch (type)
        {
        case 0:
            wave = sin((note->m_progress * 6.2831853 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            break;
        case 1:
            wave = sin((note->m_progress * 6.2831853 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            wave += sin((note->m_progress * 12.56637 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            wave /= 2;
            break;
        case 2:
            wave = sin((note->m_progress * 6.2831853 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            wave += sin((note->m_progress * 12.56637 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            wave += sin((note->m_progress * 18.8496 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            wave /= 3;
            break;
        case 3:
            wave = sin((note->m_progress * 6.2831853 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            wave += sin((note->m_progress * 6.28 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            wave /= 2;
            break;
        default:
            wave = sin((note->m_progress * 6.2831853 * note->m_height) / stk::Stk::sampleRate()) * (note->m_velocity / 65535.0);
            break;
        }
        if (note->m_progress < 1000)
            wave *= note->m_progress / 1000.0;
        if (note->m_length < 1000)
            wave *= note->m_length / 1000.0;
        StereoSample out(wave * abs(note->m_pan - 32767) / 65535.0, wave * abs(note->m_pan + 32767) / 65535.0);
        note->m_progress++;
        return out;
    }
    void loadFromFile(std::string path) {
        std::ifstream file;
        try
        {
            file.open(path);
            char nbr = '0';
            file >> nbr;
            if (nbr == '0') type = 0;
            if (nbr == '1') type = 1;
            if (nbr == '2') type = 2;
            if (nbr == '3') type = 3;
            file.close();
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};
#endif