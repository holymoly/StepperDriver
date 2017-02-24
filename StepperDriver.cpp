/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "StepperDriver.h"

StepperDriver *ptrSeppers[3]; // Stores pointer to stepper obejcts
int stepperCount = 0;         // Stepper Objects created

// Constructor
StepperDriver::StepperDriver(int stepPin, int directionPin, int ms1Pin, int ms2Pin, int ms3Pin, int rstPin, int stepSpeed)
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
  _ms3Pin = ms3Pin;
  _rstPin = rstPin;

  _stepSpeed = stepSpeed;
  _remainingSteps = 50;
  _ticks = 0;
  _number = stepperCount;

  ptrSeppers[stepperCount] = this; // add to array of Objects
  stepperCount++;

  isr = &moveContinues;

  OCR0A = 0xAF;
  TIMSK0 |= (1 << OCIE0A);  // enable timer compare interrupt
}

// Enables the stepper hardware
void StepperDriver::enable()
{
  digitalWrite(_rstPin, HIGH);
}

// Disables the stepper hardware
void StepperDriver::disable()
{
  digitalWrite(_rstPin, LOW);
}

// Set Microsteps
void StepperDriver::setMicrosteps(int steps)
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
    case 9:
      // Sixteenth stepp
      digitalWrite(_ms1Pin, LOW);
      digitalWrite(_ms2Pin, LOW);
      digitalWrite(_ms3Pin, HIGH);
      break;
    default:
      // if nothing matches disable stepper
      disable();
    break;
  }
}

// only rotate amount of steps with a defined time per step
void StepperDriver::moveSteps(StepperDriver *stepper)
{
  //Serial.println(stepper->_remainingSteps);
  stepper->_ticks++;
  if(stepper->_ticks > stepper->_stepSpeed/2 && stepper->_remainingSteps > 0)
  {
    stepper->_ticks=0;
    if(digitalRead(stepper->_stepPin) == LOW)
    {
      digitalWrite(stepper->_stepPin,HIGH);
      stepper->_remainingSteps--;
    }
    else
    {
      digitalWrite(stepper->_stepPin,LOW);
    }
  }
}

// Move until stop or disabled is called
void StepperDriver::moveContinues(StepperDriver *stepper)
{
  stepper->_ticks++;
  if(stepper->_ticks > stepper->_stepSpeed/2)
  {
    stepper->_ticks=0;
    if(digitalRead(stepper->_stepPin) == LOW)
    {
      digitalWrite(stepper->_stepPin,HIGH);
    }
    else
    {
      digitalWrite(stepper->_stepPin,LOW);
    }
  }
}

// Stops the stepper motor from rotating
void StepperDriver::activate(Mode mode)
{
  switch (mode) {
    case off:
      //hold
      disable();
      isr = &moveSteps; // isr should  be valid
      break;
    case step:
      // continues
      enable();
      isr = &moveContinues; // mode
      break;
    case cont:
      // move steps
      enable();
      isr = &moveSteps; // mode
      break;
    default:
    break;
  }
}

// Set the steps to drive during moveStepMode
void StepperDriver::setStepsToDrive(int steps)
{
  _remainingSteps = steps;
}

// Set the speed
void StepperDriver::setStepSpeed(int speed)
{
  _stepSpeed = speed;
}

// returns Stepper number
int StepperDriver::getNumber()
{
  return _number;
}


SIGNAL(TIMER0_COMPA_vect)
{
  for (int i = 0; i < stepperCount; ++i)
  {
    ptrSeppers[i]->isr(*ptrSeppers[i]);
  }
}
