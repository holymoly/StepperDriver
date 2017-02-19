/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "StepperDriver.h"

int ticks = 0;

StepperDriver::StepperDriver(int stepPin, int directionPin, int ms1Pin, int ms2Pin, int ms3Pin, int rstPin)
{
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);
  pinMode(rstPin, OUTPUT);

  digitalWrite(ms1Pin, HIGH);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, HIGH);
  digitalWrite(rstPin, LOW);


  _stepPin = stepPin;
  _directionPin = directionPin;
  _ms1Pin = ms1Pin;
  _ms2Pin = ms2Pin;
  _ms3Pin = ms2Pin;
  _rstPin = rstPin;

  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

void StepperDriver::enable()
{
  digitalWrite(_rstPin, HIGH);
}

void StepperDriver::disable()
{
  digitalWrite(_rstPin, LOW);
}

int StepperDriver::setMicrosteps(int steps)
{
  switch (steps) {
    case 0:
      // Full stepp
      digitalWrite(_ms1Pin, LOW);
      digitalWrite(_ms2Pin, LOW);
      digitalWrite(_ms3Pin, LOW);
      break;
    case 2:
      // Half stepp
      digitalWrite(_ms1Pin, HIGH);
      digitalWrite(_ms2Pin, LOW);
      digitalWrite(_ms3Pin, LOW);
      break;
    case 4:
      // Quarter stepp
      digitalWrite(_ms1Pin, LOW);
      digitalWrite(_ms2Pin, HIGH);
      digitalWrite(_ms3Pin, LOW);
      break;
    case 8:
      // Eighth stepp
      digitalWrite(_ms1Pin, HIGH);
      digitalWrite(_ms2Pin, HIGH);
      digitalWrite(_ms3Pin, LOW);
      break;
    case 16:
      // Sixteenth stepp
      digitalWrite(_ms1Pin, HIGH);
      digitalWrite(_ms2Pin, HIGH);
      digitalWrite(_ms3Pin, HIGH);
      break;
    default:
      // if nothing matches disable stepper
      disable();
    break;
  }
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect)
{
  ticks++;
  if(ticks >= 1){
     ticks = 0;
     if(digitalRead(12) == LOW)
        digitalWrite(12, HIGH);
     else
       digitalWrite(12, LOW);
  }
}
