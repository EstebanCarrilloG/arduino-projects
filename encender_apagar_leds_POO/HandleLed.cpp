#include "HandleLed.h"
#include <Arduino.h>

HandleLed::HandleLed(int buttonPin, int  ledPin)
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, 1);
  _ledPin = ledPin;
  _buttonPin = buttonPin;
  _estadoDelLed = 0;
  _estadoPrevio = 0;
}

void HandleLed::handleLed()
{
  bool buttonState = digitalRead(_buttonPin);

  if (buttonState != _estadoPrevio && buttonState == HIGH) 
    digitalWrite(_ledPin, _estadoDelLed = !_estadoDelLed);

  delay(10);
   
  _estadoPrevio = buttonState;

}
