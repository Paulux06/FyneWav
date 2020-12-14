#ifndef FYNEWAV_EFFECT
#define FYNEWAV_EFFECT
#include <note.h>
#include <stereosample.h>

/*Effect class, represents an effect in FyneWav.
 * Attributes:
 *      - None.
 * Constructors:
 *      - Effect(): Empty constructor.
 * Methodes:
 *      - tick(strsmpl): Applies audio effect to the StereoSample provided.
*/
class Effect
{
public:
    /*Empty constructor.*/
    Effect() {}
    /*Applies audio effect to the StereoSample provided.*/
    StereoSample tick(StereoSample strsmpl)
    {
        StereoSample out(0, 0);
        out.leftSample = strsmpl.leftSample;
        out.rightSample = strsmpl.rightSample;
        return out;
    }
};
#endif