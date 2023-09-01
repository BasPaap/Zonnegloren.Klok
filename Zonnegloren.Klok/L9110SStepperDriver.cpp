// 
// 
// 

#include "L9110SStepperDriver.h"

Bas::L9110SStepperDriver::L9110SStepperDriver(int numStepsPerRevolution, int pin1, int pin2, int pin3, int pin4) : StepperDriver{ numStepsPerRevolution }, pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4)
{
}

void Bas::L9110SStepperDriver::begin()
{
	stepper.setSpeed(80);
}

void Bas::L9110SStepperDriver::step(long numSteps)
{	
	stepper.step(-numSteps);
}
