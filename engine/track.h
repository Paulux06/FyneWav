#ifndef FYNEWAV_TRACK
#define FYNEWAV_TRACK
#include <pattern.h>
#include <vector>

/* Track class, represents a Track in FyneWav
 * Attributes:
 *      - m_patterns: Track's Pattern list
 *      - m_index: Track's index in arranger
 *      - m_name: Track's name
 *      - m_color: Track's 4 bit color (FFFF is the max, only 3 are used)
 * Constructors:
 *      - Track(): Empty constructor
 *      - Track(name, index, color): name, index, color constructor
 *      - Track(name, index, color, patternList): Full constructor
 * Methodes:
 *      - changeIndexBy(amount): change track index by [amount]
 *      - changeIndexTo(newValue): change track index to [newValue]
 *      - changeNameTo(newValue): change track name to [newValue]
 *      - changeColorTo(newValue): change track color to [newValue]
 *      - addPattern(): adds a pattern in the track and returns it
 *      - addPattern(pattern): adds the pattern in the track
 */
class Track
{
public:
    /*Track's Pattern list*/
    std::vector<Pattern> m_patterns;
    /*Track's index in arranger*/
    unsigned short m_index;
    /*Track's name*/
    std::string m_name;
    /*Track's 4 bit color (FFFF is the max, only 3 are used)*/
    unsigned short m_color;

    /*Empty constructor*/
    Track(): m_name("Empty track"), m_index(0), m_color(4095) {}
    /*name, index, color constructor*/
    Track(std::string name, unsigned short index, unsigned short color)
    {
        m_name = name; m_index = index; m_color = color;
    }
    /*Full constructor*/
    Track(std::string name, unsigned short index, unsigned short color, std::vector<Pattern> patternList)
    {
        m_name = name; m_index = index; m_color = color;
        m_patterns = patternList;
    }

    /*change track index by [amount]*/
    void changeIndexBy(unsigned short amount)
    {

    }
    /*change track index to [newValue]*/
    void changeIndexTo(unsigned short newValue)
    {
        // TODO
    }
    /*change track name to [newValue]*/
    void changeNameTo(std::string newValue)
    {
        // TODO
    }
    /*change track color to [newValue]*/
    void changeColorTo(unsigned short newValue)
    {
        // TODO
    }
    /*adds a pattern in the track and returns it*/
    Pattern* addPattern()
    {
        // TODO
    }
    /*adds the pattern in the track*/
    void addPattern(Pattern pattern)
    {
        // TODO
    }
};
#endif