// StepperDriver.h

#ifndef _STEPPERDRIVER_h
#define _STEPPERDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Bas
{
	class StepperDriver
	{
		int numStepsPerRevolution;

	public:
		StepperDriver(int numStepsPerRevolution);		
		virtual void begin();
		virtual void step(long numSteps);
		int getNumStepsPerRevolution();
	};
}


#endif

