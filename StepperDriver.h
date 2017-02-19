/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef StepperDriver_h
#define StepperDriver_h

#include "Arduino.h"

class StepperDriver
{
  public:
    StepperDriver(int stepPin, int directionPin, int ms1Pin, int ms2Pin, int ms3Pin, int rstPin);
    void enable();
    void disable();
    int setMicrosteps(int steps); //0,2,4,8,16;  wrong values returns 1 and disables stepper
  private:
    int _stepPin;
    int _directionPin;
    int _ms1Pin;
    int _ms2Pin;
    int _ms3Pin;
    int _rstPin;
};

#endif
