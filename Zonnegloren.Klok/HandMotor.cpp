// 
// 
// 

#include "HandMotor.h"


Bas::HandMotor::HandMotor(StepperDriver* stepperDriver) : stepperDriver{ stepperDriver }, numStepsToTake(0)
{	
}

void Bas::HandMotor::begin()
{
	stepperDriver->begin();
}

void Bas::HandMotor::revolve(float numRevolutions)
{
	numStepsToTake += numRevolutions * stepperDriver->getNumStepsPerRevolution();

	if (numStepsToTake >= 1.0 || numStepsToTake <= -1.0)
	{
		stepperDriver->step(floor(numStepsToTake));
		numStepsToTake -= floor(numStepsToTake);
	}
}