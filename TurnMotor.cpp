#include "TurnMotor.h" 
/*
                CH A    CH B
Direction	D12	D13
PWM	        D3	D11
Brake	        D9	D8
Current Sensing	A0	A1
*/
const byte turnDirectionPin = 12; //CH A - HIGH = left and LOW = right
const byte turnPMWPin = 3;        //CH A
const byte turnBrakePin = 9;      //CH A 

TurnMotor::TurnMotor()
{
  //Establish motor direction toggle pin
  pinMode(turnDirectionPin, OUTPUT);
  
  //Establish motor brake pin
  pinMode(turnBrakePin, OUTPUT); 
  
  //Turn on motor brake
  digitalWrite(turnBrakePin, HIGH);
}
TurnMotor::~TurnMotor(){/*nothing to destruct*/}

void TurnMotor::Straighten()
{
  //Apply brake to turn motor
  digitalWrite(turnBrakePin, HIGH);
}

void TurnMotor::TurnLeft()
{
  Turn(HIGH);
}

void TurnMotor::TurnRight()
{
  Turn(LOW);
}

void TurnMotor::Turn(bool directionValue)
{
    //turn off brake
    digitalWrite(turnBrakePin, LOW);

    //set turn motor direction
    digitalWrite(turnDirectionPin, directionValue);

    //activate turn motor
    analogWrite(turnPMWPin, 255);
}
