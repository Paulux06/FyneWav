#ifndef FYNEWAV_ENGINE
#define FYNEWAV_ENGINE
#include <RtAudio.h>
#include <plexer.h>
#include <chrono>
using namespace stk;

// The TickData structure holds all the class instances and data that
// are shared by the various processing functions.
struct TickData
{
    Plexer plexer;
    // Default constructor.
    TickData() {}
};

TickData data;
RtAudio dac;
double soundLevel;
double procLevel;
std::chrono::steady_clock::time_point lastTickCall = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point newTickCall;
bool engine_enabled = false;

// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData)
{
    lastTickCall = std::chrono::steady_clock::now();
    TickData *data = (TickData *)userData;
    register StkFloat *samples = (StkFloat *)outputBuffer;
    double level = 0;
    for (unsigned int i = 0; i < nBufferFrames; i++)
    {
        StereoSample render = data->plexer.tick();
        *samples++ = render.leftSample;
        *samples++ = render.rightSample;
        level += abs(render.leftSample + render.rightSample);
    }
    soundLevel = level * 75 / nBufferFrames;
    int tickTime = nBufferFrames*1000 / Stk::sampleRate(); // tick time in microseconds
    newTickCall = std::chrono::steady_clock::now();
    int delta = std::chrono::duration_cast<std::chrono::microseconds>(newTickCall - lastTickCall).count();
    procLevel = (delta / tickTime);
    return 0;
}

int enable()
{
    // Set the global sample rate
    Stk::setSampleRate(44100.0);

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 2;
    RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    try
    {
        dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&data);
    }
    catch (RtAudioError &error)
    {
        error.printMessage();
        goto cleanup;
    }

    try
    {
        dac.startStream();
    }
    catch (RtAudioError &error)
    {
        error.printMessage();
        goto cleanup;
    }
    engine_enabled = true;
    return 0;

cleanup:
    return 1;
}

int disable()
{

    // Shut down the callback and output stream.
    try
    {
        dac.closeStream();
    }
    catch (RtAudioError &error)
    {
        error.printMessage();
    }
    engine_enabled = false;
    return 0;
}

int loadFile(std::string path)
{
    data.plexer.openFile(path);
    return 0;
}
int stopFile()
{
    data.plexer.closeFile();
    return 0;
}
void noteOn(unsigned short h, unsigned short v, unsigned int l, short p)
{
    //if (data.plexer.mainChannel.m_vsts.size() > 0)
    //    data.plexer.mainChannel.m_vsts[0].NoteOn(h, v, l, p);
    data.plexer.mainChannel.getVst(0)->noteOn(h, v, l, p);
}
void setVolume(unsigned int volume)
{
    data.plexer.mainChannel.getVst(0)->m_volume = volume;
}
void loadFromFile(std::string path)
{
    data.plexer.mainChannel.getVst(0)->m_generator.loadFromFile(path);
}
#endif