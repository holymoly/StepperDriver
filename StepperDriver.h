/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef StepperDriver_h
#define StepperDriver_h

#include "Arduino.h"

enum Mode { off, step, cont };

class StepperDriver
{
  public:
    StepperDriver(int stepPin, int directionPin, int ms1Pin, int ms2Pin, int ms3Pin, int rstPin, int stepSpeed);

    void setMicrosteps(int steps); //0,2,4,8,16;  wrong values and disables stepper
    void activate(Mode mode); //0=off,1=continues,2=moveSteps

    void disable(); // sets reset pin to LOW
    void enable();  // sets reset pin to HIGH

    void setStepsToDrive(int steps);
    void setStepSpeed(int speed);

    void (*isr)(StepperDriver);
    void static moveSteps(StepperDriver *stepper);
    void static moveContinues(StepperDriver *stepper); // dummy is needed because of function pointer, to have the same amount of  args as moveSteps
    int getNumber();
    int stepSpeed;

  private:
    int _stepPin;
    int _directionPin;
    int _ms1Pin;
    int _ms2Pin;
    int _ms3Pin;
    int _rstPin;
    int _number;
    int _stepSpeed;
    int _remainingSteps;
    int _ticks;


};

#endif
