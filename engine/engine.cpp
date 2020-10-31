#include <node.h>
#include <FileWvIn.h>
#include <RtAudio.h>
#include <plexer.h>
#include <iostream>
using namespace stk;

// The TickData structure holds all the class instances and data that
// are shared by the various processing functions.
struct TickData {
    Plexer plexer;
    FileWvIn fileInput;
    // Default constructor.
    TickData() {}
};

TickData data;
RtAudio dac;
double soundLevel;
bool engine_enabled = false;
int w=442;
Vst vst = Vst(Generator(), 1);

// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    TickData *data = (TickData *) userData;
    register StkFloat *samples = (StkFloat *) outputBuffer;
    double level = 0;
    for (unsigned int i=0; i<nBufferFrames; i++) {
        StereoSample render = vst.tick();
        *samples++ = render.leftSample;
        *samples++ = render.rightSample;
        level += abs(render.leftSample+render.rightSample);
    }
    w++;
    soundLevel = level / nBufferFrames / 2;
    return 0;
}

int enable()
{
    // Set the global sample rate and rawwave path before creating class instances.
    Stk::setSampleRate(44100.0);

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 2;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    try {
        dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&data );
    }
    catch ( RtAudioError& error ) {
        error.printMessage();
        goto cleanup;
    }

    try {
        dac.startStream();
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
        goto cleanup;
    }
    engine_enabled = true;
    return 0;

cleanup:
    return 1;
}

int disable() {

    // Shut down the callback and output stream.
    try {
        dac.closeStream();
    }
    catch ( RtAudioError &error ) {
        error.printMessage();
    }
    engine_enabled = false;
    return 0;
}

int loadFile(std::string path) {
    data.fileInput.openFile(path);
    return 0;
}
int stopFile() {
    data.fileInput.closeFile();
    return 0;
}
void noteOn(unsigned short h, unsigned short v, unsigned int l, short p) {
    //if (data.plexer.mainChannel.m_vsts.size() > 0)
    //    data.plexer.mainChannel.m_vsts[0].NoteOn(h, v, l, p);
    vst.noteOn(h, v, l, p);
}

namespace fynewav {
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::Number;
    using v8::Value;
    using v8::String;
    using v8::Boolean;

    void Enable(const FunctionCallbackInfo<Value>&args) {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double) enable());
        args.GetReturnValue().Set(total);
    }
    void Disable(const FunctionCallbackInfo<Value>&args) {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double) disable());
        args.GetReturnValue().Set(total);
    }
    void LoadFile(const FunctionCallbackInfo<Value>&args) {
        Isolate *isolate = args.GetIsolate();
        String::Utf8Value str(isolate, args[0]);
        std::string path(*str);
        auto total = Number::New(isolate, (double) loadFile(path));
        args.GetReturnValue().Set(total);
    }
    void StopFile(const FunctionCallbackInfo<Value>&args) {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double) stopFile());
        args.GetReturnValue().Set(total);
    }
    void NoteOn(const FunctionCallbackInfo<Value>&args) {
        Isolate *isolate = args.GetIsolate();
        double height; args[0]->NumberValue(isolate->GetCurrentContext()).To(&height);
        double velocity; args[1]->NumberValue(isolate->GetCurrentContext()).To(&velocity);
        double length; args[2]->NumberValue(isolate->GetCurrentContext()).To(&length);
        double pan; args[3]->NumberValue(isolate->GetCurrentContext()).To(&pan);
        noteOn((unsigned short) height, (unsigned short) velocity, (unsigned int) length, (short) pan);
        auto total = Number::New(isolate, 0);
        args.GetReturnValue().Set(total);
    }
    void GetSoundLevel(const FunctionCallbackInfo<Value>&args) {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double) soundLevel);
        args.GetReturnValue().Set(total);
    }
    void GetEngineEnabled(const FunctionCallbackInfo<Value>&args) {
        Isolate *isolate = args.GetIsolate();
        auto total = Boolean::New(isolate, engine_enabled);
        args.GetReturnValue().Set(total);
    }

    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "enable", Enable);
        NODE_SET_METHOD(exports, "disable", Disable);
        NODE_SET_METHOD(exports, "loadFile", LoadFile);
        NODE_SET_METHOD(exports, "stopFile", StopFile);
        NODE_SET_METHOD(exports, "getSoundLevel", GetSoundLevel);
        NODE_SET_METHOD(exports, "getEngineEnabled", GetEngineEnabled);
        NODE_SET_METHOD(exports, "noteOn", NoteOn);
    }
    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
}