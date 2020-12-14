#ifndef FYNEWAV_MAZETRO
#define FYNEWAV_MAZETRO
#include <track.h>
#include <vector>

/* Mazetro class, groups all Tracks in FyneWav
 * Attributes:
 *      - m_tracks: mazetro's Tracks list
 * Constructors:
 *      - Mazetro(): Empty constructor
 * Methodes:
 *      - methode(variable): changes something to [variable]
 */
class Mazetro
{
public:
    /*mazetro's Tracks list*/
    std::vector<Pattern> m_patterns;

    /*Empty constructor*/
    Mazetro() {}

    /*changes something to [variable]*/
    void methode(unsigned short variable)
    {

    }
};
#endif