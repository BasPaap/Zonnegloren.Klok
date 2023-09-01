// Clock.h

#ifndef _CLOCK_h
#define _CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Time.h"

namespace Bas
{
	class Clock
	{
		const int NUM_HOURS_IN_DAY = 12;
		const int NUM_MINUTES_IN_HOUR = 60;
		const int NUM_SECONDS_IN_MINUTE = 60;
		const int NUM_MILLISECONDS_IN_SECOND = 1000;
				
		Time time{ 0, 0 };
		float constantSpeed = 1;
		
		bool isRunningAtVariableSpeed = false;
		Time variableSpeedStartTime = NULL;
		float variableSpeedStartSpeed;
		TimeSpan variableSpeedDuration;
		float variableSpeedEndSpeed;
								
	public:
		Clock();
		void begin();
		void setTime(int hour, int minute);
		void getTime(float* hour, float* minute);
		float getConstantSpeed();
		void setConstantSpeed(float speed);
		void setVariableSpeed(int startHour, int startMinute, int durationInMinutes, float startSpeed, float endSpeed);
		void getVariableSpeed(int* startHour, int* startMinute, int* durationInMinutes, float* startSpeed, float* endSpeed);
		float getCurrentSpeed();
		void update();
	};
}

#endif

