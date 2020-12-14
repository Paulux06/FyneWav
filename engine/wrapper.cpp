#include <node.h>
#include <engine.h>

namespace fynewav
{
    using v8::Boolean;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Value;

    void Enable(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double)enable());
        args.GetReturnValue().Set(total);
    }
    void Disable(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double)disable());
        args.GetReturnValue().Set(total);
    }
    void LoadFile(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        String::Utf8Value str(isolate, args[0]);
        std::string path(*str);
        auto total = Number::New(isolate, (double)loadFile(path));
        args.GetReturnValue().Set(total);
    }
    void StopFile(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double)stopFile());
        args.GetReturnValue().Set(total);
    }
    void NoteOn(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        double height;
        args[0]->NumberValue(isolate->GetCurrentContext()).To(&height);
        double velocity;
        args[1]->NumberValue(isolate->GetCurrentContext()).To(&velocity);
        double length;
        args[2]->NumberValue(isolate->GetCurrentContext()).To(&length);
        double pan;
        args[3]->NumberValue(isolate->GetCurrentContext()).To(&pan);
        noteOn((unsigned short)height, (unsigned short)velocity, (unsigned int)length, (short)pan);
        auto total = Number::New(isolate, 0);
        args.GetReturnValue().Set(total);
    }
    void SetVolume(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        double volume;
        args[0]->NumberValue(isolate->GetCurrentContext()).To(&volume);
        setVolume((unsigned int)volume);
        auto total = Number::New(isolate, 0);
        args.GetReturnValue().Set(total);
    }
    void LoadFromFile(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        String::Utf8Value str(isolate, args[0]);
        std::string path(*str);
        loadFromFile(path);
        auto total = Number::New(isolate, 0);
        args.GetReturnValue().Set(total);
    }
    void GetSoundLevel(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double)soundLevel);
        args.GetReturnValue().Set(total);
    }
    void GetProcLevel(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        auto total = Number::New(isolate, (double)procLevel);
        args.GetReturnValue().Set(total);
    }
    void GetEngineEnabled(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        auto total = Boolean::New(isolate, engine_enabled);
        args.GetReturnValue().Set(total);
    }

    void Initialize(Local<Object> exports)
    {
        NODE_SET_METHOD(exports, "enable", Enable);
        NODE_SET_METHOD(exports, "disable", Disable);
        NODE_SET_METHOD(exports, "loadFile", LoadFile);
        NODE_SET_METHOD(exports, "stopFile", StopFile);
        NODE_SET_METHOD(exports, "getSoundLevel", GetSoundLevel);
        NODE_SET_METHOD(exports, "getProcLevel", GetProcLevel);
        NODE_SET_METHOD(exports, "getEngineEnabled", GetEngineEnabled);
        NODE_SET_METHOD(exports, "noteOn", NoteOn);
        NODE_SET_METHOD(exports, "setVolume", SetVolume);
        NODE_SET_METHOD(exports, "loadFromFile", LoadFromFile);
    }
    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
} // namespace fynewav