#include <napi.h>
#include <LogitechLEDLib.h>
#include "functions.h"

using namespace Napi;

// Napi::String Method(const Napi::CallbackInfo& info) {
//   Napi::Env env = info.Env();
//   return Napi::String::New(env, "world");
// }

Napi::Boolean W_LogiLedInit(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = LogiLedInit();
  return Napi::Boolean::New(env, result);
}

Napi::Boolean W_LogiLedSaveCurrentLighting(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = LogiLedSaveCurrentLighting();
  return Napi::Boolean::New(env, result);
}

Napi::Boolean W_LogiLedRestoreLighting(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = LogiLedRestoreLighting();
  return Napi::Boolean::New(env, result);
}

Napi::Boolean W_LogiLedSetLighting(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Invalid number of arguments passed. Expected 3").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  if(!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong argument types. Expected integers").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  int redPercentage = info[0].As<Napi::Number>().Int32Value();
  int bluePercentage = info[1].As<Napi::Number>().Int32Value();
  int greenPercentage = info[2].As<Napi::Number>().Int32Value();
  if(!inRange(redPercentage, 0, 100) || !inRange(bluePercentage, 0, 100) || !inRange(redPercentage, 0, 100)) {
    Napi::TypeError::New(env, "Invalid range. Arguments must be integers within 0 <= x <= 100").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }



  bool result = LogiLedSetLighting(redPercentage, bluePercentage, greenPercentage);
  return Napi::Boolean::New(env, result);
}


// my implementation of the rest functions

Napi::Boolean W_LogiLedSetLightingForKeyWithScanCode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  
  // if(env.length() < 3){
  //   Napi::TypeError::New(env, "Few arguments were provided. Required 4, keyname, red, green and blue").ThrowAsJavaScriptException();
  //   return Napi::Boolean::New(env, false);
  // }

  // bool result = LogiLedSetLightingForKeyWithKeyName(LogiLed::KeyName::SEMICOLON,99,0,0);
  bool result = LogiLedSetLightingForKeyWithScanCode(info[0].As<Napi::Number>().Int32Value(),0,100,0);
  return Napi::Boolean::New(env, result);
}

// my code is above


Napi::Object Init(Napi::Env env, Napi::Object exports) {
  // exports.Set(Napi::String::New(env, "LogitechLed"),
  //             Napi::Function::New(env, Method));
  exports.Set(Napi::String::New(env, "LogiLedInit"),
              Napi::Function::New(env, W_LogiLedInit));
  exports.Set(Napi::String::New(env, "LogiLedSaveCurrentLighting"),
              Napi::Function::New(env, W_LogiLedSaveCurrentLighting));
  exports.Set(Napi::String::New(env, "LogiLedRestoreLighting"),
              Napi::Function::New(env, W_LogiLedRestoreLighting));
  exports.Set(Napi::String::New(env, "LogiLedSetLighting"),
              Napi::Function::New(env, W_LogiLedSetLighting));

  // my code is below thi line
  exports.Set(Napi::String::New(env, "LogiLedSetLightingForKeyWithScanCode"),
              Napi:: Function::New(env, W_LogiLedSetLightingForKeyWithScanCode));
  // my code is above this code


  return exports;
}

NODE_API_MODULE(addon, Init)
