#ifndef RgbLed_H
#define RgbLed_H

#include "Arduino.h"
#include "pins_arduino.h"

class RgbLed {
public:
  RgbLed();
  ~RgbLed();
  void Setup(byte commonPin, byte redPin, byte greenPin, byte bluePin);
  void SetColor(byte r, byte g, byte b);
  void TurnOff();
};
#endif
