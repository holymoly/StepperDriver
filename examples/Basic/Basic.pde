#include <StepperDriver.h>


// Stepper initialisieren Step, Direction, ms1, ms2, ms3, Reset
StepperDriver stepperDirver(12,11,10,9,8,7);

void setup(void)
{
  stepperDirver.setMicrosteps(16);
  //stepperDirver.disable();
  stepperDirver.enable();
}

void loop(void)
{
}
