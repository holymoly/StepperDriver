# StepperDriver

Arduino Stepper Motor library that is completly interrupt based. Build for [big easy driver](http://www.schmalzhaus.com/BigEasyDriver/index.html) compatible Boards.

## Overview
 * can control multiple Stpper Motors
 * timer interrupts use for stepping (currently timer0)

## Methods
#### create stepper motor object
  ```
StepperDriver(int stepPin, int directionPin, int ms1Pin, int ms2Pin, int ms3Pin, int rstPin, int stepSpeed)
  ```
example 
  ```
StepperDriver stepperDriver(12,11,14,15,16,7,2);
  ```
    
    
#### set mode
  ```
activate(Mode mode)
  ```
Mode can bee cont, step or off
    
example 
  ```
stepperDriver.activate(cont);
  ```
#### set steps to drive
  ```
setStepsToDrive(int steps);
  ```
Mode can bee cont, step or off
    
example 
    
  ```
    // set the steps
    stepperDriver.setStepsToDrive(200);
    // start rotation
     stepperDriver.activate(step);
  ```
## Examples
### Rotate Motor 1 Round with 1/16 stepping
  ```
#include <StepperDriver.h>


// PINS (Step PIN, DIRECTION Pin, MS1 Pin, MS2 Pin, MS3 Pin,RST/EN Pin, step speed in ms)
StepperDriver stepperDriver(12,11,14,15,16,7,2);

void setup(void)
{
  //*************
  // Set Microsteps
  stepperDriver.setMicrosteps(16);
  // Set Steps and activate Motor in step mode
  stepperDriver.setStepsToDrive(3600);
  stepperDriver.activate(step);
  //*************
}

void loop(void)
{
}
  ```
### Rotate Motor continues with full step width
  ```
#include <StepperDriver.h>


// PINS (Step PIN, DIRECTION Pin, MS1 Pin, MS2 Pin, MS3 Pin,RST/EN Pin, step speed in ms)
StepperDriver stepperDriver(12,11,14,15,16,7,2);

void setup(void)
{
  //*************
  // Activat continues
  stepperDriver.activate(cont);
  //*************
}

void loop(void)
{
}
  ```
