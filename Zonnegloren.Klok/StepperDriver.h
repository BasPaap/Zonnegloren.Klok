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
	public:
		virtual void step(long numSteps) = 0;
	};
}


#endif

