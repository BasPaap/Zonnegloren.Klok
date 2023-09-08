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
		float constantSpeed = 1;
		
		bool isRunningAtVariableSpeed = false;
		Time variableSpeedStartTime = NULL;
		float variableSpeedStartSpeed;
		Time variableSpeedEndTime;
		float variableSpeedEndSpeed;
								
	public:
		Clock();
		void begin();
		void setTime(uint8_t hour, uint8_t minute);
		void getTime(float* hour, float* minute);
		void getAbsoluteTime(uint8_t* hour, uint8_t* minute);
		float getConstantSpeed();
		void setConstantSpeed(float speed);
		void setVariableSpeed(uint8_t startHour, uint8_t startMinute, uint8_t endHour, uint8_t endMinute, float startSpeed, float endSpeed);
		void getVariableSpeed(uint8_t* startHour, uint8_t* startMinute, uint8_t* endHour, uint8_t* endMinute, float* startSpeed, float* endSpeed);
		float getCurrentSpeed();
		void update();
	};
}

#endif

