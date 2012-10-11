#ifndef DriveMotor_H
#define DriveMotor_H

#include "Arduino.h"
#include "pins_arduino.h"

class DriveMotor {
public:
  DriveMotor();
  ~DriveMotor();
  void Stop();
  void Forward(byte speedPMW);
  void Backward(byte speedPMW);  
  void Drive(boolean directionVal, byte speedPMW);
  boolean IsMovingForward();
  boolean IsMovingBackward();
  float GetCurrentAmps();
};
#endif
