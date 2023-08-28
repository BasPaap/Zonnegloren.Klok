// Clock.h

#ifndef _CLOCK_h
#define _CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Bas
{
	class Clock
	{
		const int NUM_WHOLE_STEPS_PER_ROTATION = 720;
		const int STEP_RESOLUTION = 1; // whole steps = 1, half steps = 2, etc
		const int NUM_STEPS_PER_ROTATION = NUM_WHOLE_STEPS_PER_ROTATION * STEP_RESOLUTION;
		const int TOTAL_HOURS = 12;
		const int TOTAL_MINUTES = 60;
		const int TOTAL_SECONDS = 60;
		const int TOTAL_MILLISECONDS = 1000;
		const int NUM_STEPS_PER_HOUR = NUM_STEPS_PER_ROTATION / TOTAL_HOURS;
		const int NUM_STEPS_PER_MINUTE = NUM_STEPS_PER_ROTATION / TOTAL_MINUTES;

		int currentHour;
		int currentMinute;
		int currentSecond;
		int currentMillisecond;

		unsigned long lastMillis;

		float constantSpeed = 1;

		float numHourStepsToTake;
		float numMinuteStepsToTake;

		int variableSpeedStartHour;
		int variableSpeedStartMinute;
		float variableSpeedStartSpeed;
		int variableSpeedEndHour;
		int variableSpeedEndMinute;
		float variableSpeedEndSpeed;
		int mod(int a, int n);
		void getNewTime(int& newHour, int& newMinute, int& newSecond, int& newMillisecond);

	public:
		Clock();
		void begin();
		void calibrate(int currentlyDisplayedHour, int currentlyDisplayedMinute);
		void setTime(int hour, int minute);
		void getTime(int* hour, int* minute);
		float getConstantSpeed();
		void setConstantSpeed(float speed);
		void setVariableSpeed(int startHour, int startMinute, float startSpeed, int endHour, int endMinute, float endSpeed);
		void getVariableSpeed(int* startHour, int* startMinute, float* startSpeed, int* endHour, int* endMinute, float* endSpeed);
		void update();
	};
}

#endif

