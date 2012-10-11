#ifndef TurnMotor_H
#define TurnMotor_H

#include "Arduino.h"
#include "pins_arduino.h"

class TurnMotor {
public:
  TurnMotor();
  ~TurnMotor();
  void Straighten();
  void TurnLeft();
  void TurnRight();
  void Turn(bool directionValue);
};
#endif
