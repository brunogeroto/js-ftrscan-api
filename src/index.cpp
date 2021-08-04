#include "lib/ftrScanAPI.h"
#include <napi.h>

Napi::Value _ftrScanOpenDevice(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto handler = ftrScanOpenDevice();
    if (handler == NULL) {
        return Napi::Number::New(env, 0);
    }

    return Napi::External<void>::New(env, ftrScanOpenDevice());
}

void _ftrScanCloseDevice(const Napi::CallbackInfo& info) {
    auto handler = info[0].As<Napi::External<void>>().Data();

    ftrScanCloseDevice(handler);
    return;
}

Napi::Boolean _ftrScanGetFrame(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto handler = info[0].As<Napi::External<void>>().Data();
    auto pBuffer = info[1].As<Napi::Buffer<unsigned char>>().Data();

    return Napi::Boolean::New(env, ftrScanGetFrame(handler, pBuffer, NULL));
}

Napi::Boolean _ftrScanIsFingerPresent(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto handler = info[0].As<Napi::External<void>>().Data();

    return Napi::Boolean::New(env, ftrScanIsFingerPresent(handler, NULL));
}

Napi::Object _ftrScanGetImageSize(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto handler = info[0].As<Napi::External<void>>().Data();
    FTRSCAN_IMAGE_SIZE imageSize;
    ftrScanGetImageSize(handler, &imageSize);

    Napi::Object imageInfo = Napi::Object::New(env);
    imageInfo.Set("height", imageSize.nHeight);
    imageInfo.Set("width", imageSize.nWidth);
    imageInfo.Set("size", imageSize.nImageSize);

    return imageInfo;
}

Napi::Number _ftrScanGetLastError(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto error = ftrScanGetLastError();
    return Napi::Number::New(env, error);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "ftrScanOpenDevice"),
        Napi::Function::New(env, _ftrScanOpenDevice)
    );

    exports.Set(
        Napi::String::New(env, "ftrScanCloseDevice"),
        Napi::Function::New(env, _ftrScanOpenDevice)
    );

    exports.Set(
        Napi::String::New(env, "ftrScanGetFrame"),
        Napi::Function::New(env, _ftrScanGetFrame)
    );

    exports.Set(
        Napi::String::New(env, "ftrScanIsFingerPresent"),
        Napi::Function::New(env, _ftrScanIsFingerPresent)
    );

    exports.Set(
        Napi::String::New(env, "ftrScanGetImageSize"),
        Napi::Function::New(env, _ftrScanGetImageSize)
    );

    exports.Set(
        Napi::String::New(env, "ftrScanGetLastError"),
        Napi::Function::New(env, _ftrScanGetLastError)
    );

    return exports;
}

NODE_API_MODULE(nodeFtrscanApi, Init)
