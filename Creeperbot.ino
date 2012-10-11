#include "PingSensor.h"
#include "TurnMotor.h"
#include "DriveMotor.h"
#include "RgbLed.h"

PingSensor pingSensor;
TurnMotor turnMotor;
DriveMotor driveMotor;
RgbLed rgbLed;
const byte lowSpeed = 170;
const byte highSpeed = 255;
long lastDirChange = 0;

void setup() 
{
  Serial.begin(9600); 
  rgbLed.Setup(4, 5, 6, 10);
  lastDirChange = millis();
}

void loop()
{
  long distanceInches = pingSensor.determineDistanceInInches();
  if (driveMotor.IsMovingForward())
  { 
    HandleForwardMovementDecisions(distanceInches);
  }
  else if (driveMotor.IsMovingBackward())
  {
    HandleBackwardMovementDecisions(distanceInches);
  }
  else
  {
    HandleStoppedDecisions(distanceInches);
  }
  //This delay has to be here, otherwise the ping sensor will get constant/immediate echoes and think it is close to an object.
  delay(100);
}


void HandleForwardMovementDecisions(long distanceInches)
{
  float driveAmps = driveMotor.GetCurrentAmps();
  
  //I thought that when the drive motor's amps are less the 1, the motor is running efficiently and the robot is probably moving fast (or being held off the ground).
  //But, after further testing on different terrain, this is not true...
  int redZone = (driveAmps > 1.05) ? 12 : 36;
  int ylwZone = (driveAmps > 1.05) ? 36 : 60;
  if (distanceInches < redZone)
  { 
    //No need to check the time... We need to stop! 
    //But, we need to reset the timer though because we are changing direction.
    lastDirChange = millis();
    
    SetHeadLightsRed();
    driveMotor.Stop();
    turnMotor.TurnLeft();
    driveMotor.Backward(highSpeed);
  }
  else if (distanceInches < ylwZone)
  {
    //No need to check the time, or reset the timer... We need to slow and are not changing direction!
    SetHeadLightYield();
    turnMotor.TurnRight();
    driveMotor.Forward(lowSpeed);
  }
  else
  {
    turnMotor.Straighten();
    SetHeadLightsFreeAndClear();
    driveMotor.Forward(highSpeed);
  }
}

void HandleBackwardMovementDecisions(long distanceInches)
{
  long ms = millis() - lastDirChange;
  
  //Only want to stop backing up if we've been in reverse for atleast 1 sec... 
  //TODO: ...or if we're not moving, but we need more sensors or more data on amps going to the drive motor.
  if(ms >= 1000)
  {
    if(distanceInches >= 36)
    {
      lastDirChange = millis();
      rgbLed.TurnOff();
      driveMotor.Stop();
    }
  }
}

void HandleStoppedDecisions(long distanceInches)
{
  if (distanceInches < 12)
  {
    //No need to check the time, but we need to reset the timer because we are starting to move from a stop.
    lastDirChange = millis();
    
    SetHeadLightsRed();
    driveMotor.Stop();
    turnMotor.TurnLeft();
    driveMotor.Backward(highSpeed);
  }
  else if (distanceInches < 36)
  {
    //No need to check the time, but we need to reset the timer because we are starting to move from a stop.
    lastDirChange = millis();
    
    SetHeadLightYield();
    turnMotor.TurnRight();
    driveMotor.Forward(lowSpeed);
  }
  else
  {
    //No need to check the time, but we need to reset the timer because we are starting to move from a stop.
    lastDirChange = millis();
    
    SetHeadLightsFreeAndClear();
    driveMotor.Forward(highSpeed);
  }
}

void SetHeadLightsRed()
{
  rgbLed.SetColor(255, 0, 0);
}
void SetHeadLightYield()
{
  rgbLed.SetColor(110, 17, 211);
}
void SetHeadLightsFreeAndClear()
{
  rgbLed.SetColor(0, 255, 127);
}
