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
class Channel {
    public:
        std::vector<Vst> m_vsts;
        std::vector<Channel> m_channels;
        std::vector<Effect> m_effects;

        /*Empty constructor.*/
        Channel() {}

        void addVst(Vst vst) {
            m_vsts.push_back(vst);
        }
        void addChannel(Channel channel) {
            m_channels.push_back(channel);
        }
        void addEffect(Effect effect) {
            m_effects.push_back(effect);
        }
        /*Returns all the sounds from m_vsts and m_channels's vsts with m_effects applied on them.*/
        StereoSample tick() {
            StereoSample out(0, 0);
            for (auto i = m_vsts.begin(); i < m_vsts.end(); i++) {
                out += i->tick();
            }
            for (auto i = m_channels.begin(); i < m_channels.end(); i++) {
                out += i->tick();
            }
            for (auto i = m_effects.begin(); i < m_effects.end(); i++) {
                out = i->tick(out);
            }
            return out;
        }
};