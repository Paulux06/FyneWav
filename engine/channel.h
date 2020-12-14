#ifndef FYNEWAV_CHANNEL
#define FYNEWAV_CHANNEL
#include <vector>
#include <vst.h>
#include <effect.h>

/*Effect class, represents an effect in FyneWav.
 * Attributes:
 *      - m_vsts: Channel's Vsts list.
 *      - m_channels: Channel's wired Channels list.
 *      - m_effects: Channel's effects list.
 * Constructors:
 *      - Channel(): Empty constructor.
 * Methodes:
 *      - tick(): Returns all the sounds from m_vsts and m_channels's vsts with m_effects applied on them.
*/
class Channel
{
private:
    Vst *m_vsts;
    Channel *m_channels;
    Effect *m_effects;

public:
    /*Empty constructor.*/
    Channel() {}

    /*Add the vst to the channel's vst list*/
    void addVst(Vst *vst)
    {
        unsigned short new_length = sizeof(m_vsts) / sizeof(Vst) + 1;
        Vst *new_tab = new Vst[new_length];
        for (unsigned short i = 0; i < new_length-1; i++)
        {
            new_tab[i] = m_vsts[i];
        }
        new_tab[new_length-1] = *vst;
        delete[] m_vsts;
        m_vsts = new_tab;
        std::cout << "new vst added" << std::endl;
        std::cout << "now, m_vsts length = " << sizeof(m_channels) / sizeof(Channel) << std::endl;
    }
    /*Add the channel to the channel's channel list*/
    void addChannel(Channel *channel)
    {
        unsigned short new_length = sizeof(m_channels) / sizeof(Channel) + 1;
        Channel *new_tab = new Channel[new_length];
        for (unsigned short i = 0; i < new_length-1; i++)
        {
            new_tab[i] = m_channels[i];
        }
        new_tab[new_length-1] = *channel;
        delete[] m_channels;
        m_channels = new_tab;
        std::cout << "new channel added" << std::endl;
        std::cout << "now, m_channels length = " << sizeof(m_channels) / sizeof(Channel) << std::endl;
    }
    /*Add the effect to the channel's effect list*/
    void addEffect(Effect *effect)
    {
        unsigned short new_length = sizeof(m_effects) / sizeof(Effect) + 1;
        Effect *new_tab = new Effect[new_length];
        for (unsigned short i = 0; i < new_length-1; i++)
        {
            new_tab[i] = m_effects[i];
        }
        new_tab[new_length-1] = *effect;
        delete[] m_effects;
        m_effects = new_tab;
        std::cout << "new effect added" << std::endl;
        std::cout << "now, m_effects length = " << sizeof(m_channels) / sizeof(Channel) << std::endl;
    }
    /*Remove the vst at index from the channel's vst list*/
    Vst* getVst(unsigned short index)
    {
        return &m_vsts[index];
    }
    /*Remove the channel at index from the channel's channel list*/
    Channel* getChannel(unsigned short index)
    {
        return &m_channels[index];
    }
    /*Returns the effect at index from the channel's effect list*/
    Effect* getEffect(unsigned short index)
    {
        return &m_effects[index];
    }
    /*Remove the vst at index from the channel's vst list*/
    void removeVst(unsigned short index)
    {
        unsigned short length = sizeof(m_vsts) / sizeof(Vst);
        if (index > length-1) return;
        Vst *new_tab = new Vst[length-1];
        unsigned short new_i = 0;
        for (unsigned short i = 0; i < length; i++)
        {
            if (i == index) continue;
            new_tab[new_i++] = m_vsts[index];
        }
        delete[] m_vsts;
        m_vsts = new_tab;
        std::cout << "removed vst at index " << index << std::endl;
        std::cout << "now, m_vsts length = " << sizeof(m_channels) / sizeof(Channel) << std::endl;
    }
    /*Remove the channel at index from the channel's channel list*/
    void removeChannel(unsigned short index)
    {
        unsigned short length = sizeof(m_channels) / sizeof(Channel);
        if (index > length-1) return;
        Channel *new_tab = new Channel[length-1];
        unsigned short new_i = 0;
        for (unsigned short i = 0; i < length; i++)
        {
            if (i == index) continue;
            new_tab[new_i++] = m_channels[index];
        }
        delete[] m_channels;
        m_channels = new_tab;
        std::cout << "removed channel at index " << index << std::endl;
        std::cout << "now, m_channels length = " << sizeof(m_channels) / sizeof(Channel) << std::endl;
    }
    /*Remove the effect at index from the channel's effect list*/
    void removeEffect(unsigned short index)
    {
        unsigned short length = sizeof(m_effects) / sizeof(Effect);
        if (index > length-1) return;
        Effect *new_tab = new Effect[length-1];
        unsigned short new_i = 0;
        for (unsigned short i = 0; i < length; i++)
        {
            if (i == index) continue;
            new_tab[new_i++] = m_effects[index];
        }
        delete[] m_effects;
        m_effects = new_tab;
        std::cout << "removed effect at index " << index << std::endl;
        std::cout << "now, m_effects length = " << sizeof(m_channels) / sizeof(Channel) << std::endl;
    }
    /*Returns all the sounds from m_vsts and m_channels's vsts with m_effects applied on them.*/
    StereoSample tick()
    {
        StereoSample out(0, 0);
        unsigned short m_vsts_length = sizeof(m_vsts) / sizeof(Vst);
        for (unsigned short i = 0; i < m_vsts_length; i++)
        {
            out += m_vsts[i].tick();
            std::cout << "vst sending sample" << std::endl;
        }
        unsigned short m_channels_length = sizeof(m_channels) / sizeof(Channel);
        for (unsigned short i = 0; i < m_channels_length; i++)
        {
            out += m_channels[i].tick();
            std::cout << "channel sending sample" << std::endl;
        }
        unsigned short m_effects_length = sizeof(m_effects) / sizeof(Effect);
        for (unsigned short i = 0; i < m_effects_length; i++)
        {
            out += m_effects[i].tick(out);
            std::cout << "effect changing sample" << std::endl;
        }
        
        return out;
    }
};
#endif