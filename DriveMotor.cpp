#include "DriveMotor.h" 
/*
                CH A    CH B
Direction	D12	D13
PWM	        D3	D11
Brake	        D9	D8
Current Sensing	A0	A1
*/

const byte driveDirectionPin = 13; //CH B - HIGH = forwards and LOW = backwards
const byte drivePMWPin = 11;       //CH B 
const byte driveBrakePin = 8;      //CH B
int currentPin = A1;
boolean braking = HIGH;
boolean dirVal = HIGH;
byte speedVal = 0;

DriveMotor::DriveMotor()
{
  //Establish motor direction toggle pin
  pinMode(driveDirectionPin, OUTPUT);
  
  //Establish motor brake pin
  pinMode(driveBrakePin, OUTPUT); 
  
  //Turn on motor brake
  braking = HIGH;
  digitalWrite(driveBrakePin, braking);
}

DriveMotor::~DriveMotor(){/*nothing to destruct*/}

void DriveMotor::Stop()
{
  //turn on brake of drive motor
  braking = HIGH;
  digitalWrite(driveBrakePin, braking); 
}

void DriveMotor::Forward(byte speedPMW)
{
  Drive(HIGH, speedPMW);
}

void DriveMotor::Backward(byte speedPMW)
{
  Drive(LOW, speedPMW);
}

void DriveMotor::Drive(boolean directionVal, byte speedPMW)
{
  //turn off brake of drive motor
  braking = LOW;
  digitalWrite(driveBrakePin, braking); 
  
  //set drive motor backwards direction
  dirVal = directionVal;
  digitalWrite(driveDirectionPin, dirVal);
    
  //activate the drive motor
  speedVal = speedPMW;
  analogWrite(drivePMWPin, speedVal);
}

boolean DriveMotor::IsMovingForward()
{
  return !braking && dirVal == HIGH && speedVal > 0;
}
boolean DriveMotor::IsMovingBackward()
{
  return !braking && dirVal == LOW && speedVal > 0;
}

float DriveMotor::GetCurrentAmps()
{
  //See: http://www.dustynrobots.com/news/digital-signal-processing-and-filtering-motor-current-sensing/
  const float volt_per_amp = 1.65; // resolution according to hardware page
  float currentRaw = analogRead(currentPin);
  float currentVolts = currentRaw *(5.0/1024.0);
  float currentAmps = currentVolts/volt_per_amp;
  return currentAmps;
}
