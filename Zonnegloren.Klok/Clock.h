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
		const int numHoursInDay = 12;
		const int numMinutesInHour = 60;
		const int numSecondsInMinute = 60;
		const int numMillisecondsInSecond = 1000;
				
		Time time{ 0, 0 };
		float constantSpeed{ 0 };
		
		bool isRunningAtVariableSpeed = false;
		Time variableSpeedStartTime = NULL;
		float variableSpeedStartSpeed;
		Time variableSpeedEndTime;
		float variableSpeedEndSpeed;
								
	public:
		Clock();
		void begin();
		void setTime(uint8_t hours, uint8_t minutes);
		void getTime(float* hours, float* minutes);
		void getAbsoluteTime(uint8_t* hours, uint8_t* minutes);
		float getConstantSpeed();
		void setConstantSpeed(float speed);
		void setVariableSpeed(uint8_t startHours, uint8_t startMinutes, float startSpeed, uint8_t endHours, uint8_t endMinutes, float endSpeed);
		void getVariableSpeed(uint8_t* startHours, uint8_t* startMinutes, float* startSpeed, uint8_t* endHours, uint8_t* endMinutes, float* endSpeed);
		float getCurrentSpeed();
		void update();
	};
}

#endif

