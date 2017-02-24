#include <StepperDriver.h>


// PINS (Step PIN, DIRECTION Pin, MS1 Pin, MS2 Pin, MS3 Pin,RST/EN Pin, speed in ms)
StepperDriver stepperDriver(12,11,14,15,16,7,1);

void setup(void)
{
  //*************
  //Set Microsteps
  stepperDriver.setMicrosteps(16);
  //*************
  //*************
  //Set Steps and activate Motor in step mode
  stepperDriver.setStepsToDrive(3600);
  stepperDriver.activate(step);
  //*************
  delay(1000);
  //*************
  // Turn off
  stepperDriver.activate(off);
  //*************
  delay(1000);
  //*************
  // Activate motor in continues mode
  stepperDriver.activate(cont);
  //*************
}

void loop(void)
{
}
