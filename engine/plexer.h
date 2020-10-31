#include <channel.h>

class Plexer {
    public:
        Channel mainChannel;

        Plexer() {
            Vst baseVst = Vst();
            mainChannel.addVst(baseVst);
        }

        StereoSample tick() {
            return mainChannel.tick();
        }
};