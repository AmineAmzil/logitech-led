const addon = require("../build/Release/logitech-led-native");

interface LogitechLed {
  LogiLedInit: () => boolean;
  LogiLedSaveCurrentLighting: () => boolean;
  LogiLedRestoreLighting: () => boolean;
  LogiLedSetLighting: (red: number, green: number, blue: number) => boolean;
  LogiLedSetLightingForKeyWithScanCode: (scanCode: Number, red: Number, green: Number, blue: Number) => boolean;
}

export = addon as LogitechLed;
