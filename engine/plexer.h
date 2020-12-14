#ifndef FYNEWAV_PLEXER
#define FYNEWAV_PLEXER
#include <channel.h>
#include <FileWvIn.h>
#include <RtWvIn.h>

class Plexer
{
public:
    Channel mainChannel;
    double volume;
    stk::FileWvIn fileInput;

    Plexer()
    {
        Vst *baseVst = new Vst();
        mainChannel.addVst(baseVst);
        volume = 1.0;
    }

    StereoSample tick()
    {
        StereoSample out = mainChannel.tick();
        double fileSample = fileInput.tick();
        out.leftSample += fileSample;
        out.rightSample += fileSample;
        return out;
    }

    void openFile(std::string path)
    {
        try
        {
            fileInput.openFile(path);
        }
        catch(const stk::StkError& e)
        {
            std::cout << "Error playing audio file at " << path << std::endl;
        }
        
    }

    void closeFile()
    {
        fileInput.closeFile();
    }
};
#endif