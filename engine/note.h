#ifndef FYNEWAV_NOTE
#define FYNEWAV_NOTE
/**Note class, represents a note in FyneWav
 * Attributes:
 *      - m_velocity: Note velocity
 *      - m_height: Note height
 *      - m_length: Note length
 *      - m_pan: Note pan
 * Constructors:
 *      - Note(): Empty constructor
 *      - Note(height): Height constructor
 *      - Note(velocity, height, length, pan): Full constructor
 * Methodes:
 *      - changeAttributeBy(amount): change note attribute by [amount]
 *      - changeAttributeTo(newValue): change note attribute to [newValue]
*/
class Note {
    public:
        /**note velocity (max = 65 535)*/
        unsigned short m_velocity;
        /**note height (0 = C, 1=C#, 2=D, 3=D#)*/
        unsigned short m_height;
        /**note length (in samples)*/
        unsigned int m_length;
        /**note panning (max = 32 767 | min = -32 768)*/
        short m_pan;

        /**Empty constructor (pan=0, length=20, height=0, velocity=52 428)*/
        Note(): m_pan(0), m_length(20), m_height(0), m_velocity(52428) {}
        /**Height Constructor (pan=0, length=20, velocity=52 428)*/
        Note(unsigned int height): m_pan(0), m_length(20), m_velocity(52428) {
            m_height = height;
        }
        /**Full constructor*/
        Note(unsigned short height, unsigned short velocity,
             unsigned int length,   unsigned short pan) {
            m_velocity = velocity; m_height = height;
            m_length = length; m_pan = pan;
        }

        /**Change note height to [new_height]*/
        void changeHeightTo(unsigned short new_height) {m_height = new_height;}
        /**Change note height by a [delta_height] amount*/
        void changeHeightBy(short delta_height) {
            if ( (delta_height < 0 && m_height > 0) || 
                 (delta_height > 0 && m_height < 65535) )
                m_height += delta_height;
        }

        /**Change note length to [new_length]*/
        void changeLengthTo(unsigned int new_length) {m_length += new_length;}
        /**Change note length by a [delta_length] amount*/
        void changeLengthBy(int delta_length) {
            if ( (delta_length < 0 && m_length > 0) || 
                 (delta_length > 0 && m_length < 65535) )
                m_length += delta_length;
        }
        
        /**Change note velocity to [new_velocity]*/
        void changeVelocityTo(unsigned short new_velocity) {m_velocity += new_velocity;}
        /**Change note velocity by a [delta_velocity] amount*/
        void changeVelocityBy(short delta_velocity) {
            if ( (delta_velocity < 0 && m_velocity > 0) || 
                 (delta_velocity > 0 && m_velocity < 65535) )
                m_velocity += delta_velocity;
        }

        /**Change note pan to [new_pan]*/
        void changePanTo(short new_pan) {m_pan += new_pan;}
        /**Change note pan by a [delta_pan] amount*/
        void changePanBy(short delta_pan) {
            if ( (delta_pan < 0 && m_pan > -32768) || 
                 (delta_pan > 0 && m_pan < 32767) )
                m_pan += delta_pan;
        }
};
#endif