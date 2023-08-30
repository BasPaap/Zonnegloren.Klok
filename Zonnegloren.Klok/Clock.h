// Clock.h

#ifndef _CLOCK_h
#define _CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "DateTime.h"

namespace Bas
{
	class Clock
	{
		const int NUM_HOURS_IN_DAY = 12;
		const int NUM_MINUTES_IN_HOUR = 60;
		const int NUM_SECONDS_IN_MINUTE = 60;
		const int NUM_MILLISECONDS_IN_SECOND = 1000;
				
		DateTime time{ 0, 0 };
		float constantSpeed = -3600;
		
		int variableSpeedStartHour;
		int variableSpeedStartMinute;
		float variableSpeedStartSpeed;
		int variableSpeedEndHour;
		int variableSpeedEndMinute;
		float variableSpeedEndSpeed;
		
		long mod(long a, long n);
		
	public:
		Clock();
		void begin();
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

