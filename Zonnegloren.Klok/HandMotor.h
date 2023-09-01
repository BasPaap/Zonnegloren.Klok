// HandMotor.h

#ifndef _HANDMOTOR_h
#define _HANDMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "L9110SStepperDriver.h"

namespace Bas
{
	class HandMotor
	{
		StepperDriver* stepperDriver;
		float numStepsToTake;

	public:
		HandMotor(StepperDriver* stepperDriver);
		void begin();
		void revolve(float numRevolutions);
	};
}

#endif

