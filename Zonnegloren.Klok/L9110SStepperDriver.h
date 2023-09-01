// L9110SStepperDriver.h

#ifndef _L9110SSTEPPERDRIVER_h
#define _L9110SSTEPPERDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "StepperDriver.h"
#include <Stepper.h>

namespace Bas
{
	class L9110SStepperDriver : public StepperDriver
	{
		int numStepsPerRevolution = 720;
		int pin1;
		int pin2;
		int pin3;
		int pin4;

		Stepper stepper{ numStepsPerRevolution, pin1, pin2, pin3, pin4 };

	public:
		L9110SStepperDriver(int numStepsPerRevolution, int pin1, int pin2, int pin3, int pin4);		
		virtual void begin();
		virtual void step(long numSteps);
	};
}

#endif

