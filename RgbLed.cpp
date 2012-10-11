#include "RgbLed.h" 
// This assumes you're using a RadioShack #276-0028 RGB LED
// 2011-05-12: Note!  The anode is the really long pin.
// You'll need to bend it to get it into Digital8.
//
//          ||  ||  ||  ||
//          ||  ||  ||  ||
//          ||  ||  ||  ||
//          G   B   ||  ||
//                  ||  R
//                   A
//         D?   D?  D?  D? 

byte common_anode;
byte red_pin; 
byte green_pin;
byte blue_pin;   

RgbLed::RgbLed(){}

RgbLed::~RgbLed(){/*nothing to destruct*/}

void RgbLed::Setup(byte commonPin, byte redPin, byte greenPin, byte bluePin)
{
  common_anode = commonPin;
  red_pin = redPin; 
  green_pin = greenPin;
  blue_pin = bluePin;
  
  pinMode(common_anode, OUTPUT);
  digitalWrite(common_anode, HIGH);

  pinMode(red_pin, OUTPUT);
  digitalWrite(red_pin, HIGH);

  pinMode(green_pin, OUTPUT);
  digitalWrite(green_pin, HIGH);

  pinMode(blue_pin, OUTPUT);
  digitalWrite(blue_pin, HIGH);
}

void RgbLed::SetColor(byte r, byte g, byte b)
{
  analogWrite(red_pin, 255-r);
  analogWrite(blue_pin, 255-g);
  analogWrite(green_pin, 255-b);
}

void RgbLed::TurnOff()
{
  digitalWrite(red_pin, HIGH);
  digitalWrite(green_pin, HIGH);
  digitalWrite(blue_pin, HIGH);
}
