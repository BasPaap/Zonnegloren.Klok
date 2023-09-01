//

#include "StepperDriver.h"

Bas::StepperDriver::StepperDriver(int numStepsPerRevolution) : numStepsPerRevolution{ numStepsPerRevolution }
{
}

void Bas::StepperDriver::begin()
{
}

void Bas::StepperDriver::step(long numSteps)
{
}

int Bas::StepperDriver::getNumStepsPerRevolution()
{
	return this->numStepsPerRevolution;
}