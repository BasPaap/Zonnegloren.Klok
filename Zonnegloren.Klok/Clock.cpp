// 
// 
// 

#include "Clock.h"
#include "TimeSpan.h"

Bas::Clock::Clock()
{
}

void Bas::Clock::begin()
{
}

void Bas::Clock::setTime(uint8_t hour, uint8_t minute)
{
	// We'll consider the stepper motor's current positions to be the positions for currentHour and currentMinute.
	// Therefore, we need to calculate the amount of steps we need to move each hand from currentHour to hour and from currentMinute to minute.
	time = Time{ hour, minute };
}

void Bas::Clock::getTime(float* hour, float* minute)
{
	*minute = time.minute() + (time.second() / (float)numSecondsInMinute);

	const int numSecondsInHour = numSecondsInMinute * numMinutesInHour;
	*hour = time.hour() + (*minute / numSecondsInHour);	
}

void Bas::Clock::getAbsoluteTime(uint8_t* hour, uint8_t* minute)
{
	*hour = time.hour();
	*minute = time.minute();
}

float Bas::Clock::getConstantSpeed()
{
	return this->constantSpeed;
}

void Bas::Clock::setConstantSpeed(float speed)
{
	this->constantSpeed = speed;
}

void Bas::Clock::setVariableSpeed(uint8_t startHour, uint8_t startMinute, float startSpeed, uint8_t endHour, uint8_t endMinute, float endSpeed)
{
	this->variableSpeedStartTime = Time(startHour, startMinute);
	this->variableSpeedEndTime = Time(endHour, endMinute);
	this->variableSpeedStartSpeed = startSpeed;
	this->variableSpeedEndSpeed = endSpeed;
}

void Bas::Clock::getVariableSpeed(uint8_t* startHour, uint8_t* startMinute, float* startSpeed, uint8_t* endHour, uint8_t* endMinute, float* endSpeed)
{
	*startHour = this->variableSpeedStartTime.hour();
	*startMinute = this->variableSpeedStartTime.minute();
	*endHour = this->variableSpeedEndTime.hour();
	*endMinute = this->variableSpeedEndTime.minute();
	*startSpeed = this->variableSpeedStartSpeed;
	*endSpeed = this->variableSpeedEndSpeed;
}

float Bas::Clock::getCurrentSpeed()
{
	if (variableSpeedStartTime == NULL)
	{
		return constantSpeed;
	}
	else
	{
		if (time == variableSpeedStartTime)
		{
			isRunningAtVariableSpeed = true;
		}


		if (isRunningAtVariableSpeed)
		{			
			if (time == variableSpeedEndTime)
			{
				isRunningAtVariableSpeed = false;
				return constantSpeed;
			}
			else
			{
				// using variableSpeedStartTime as A and variableSpeedEndTime as B, find the inverse lerp t for time.
				float t = (float)(time.totalSeconds() - variableSpeedStartTime.totalSeconds()) / (float)(variableSpeedEndTime.totalSeconds() - variableSpeedStartTime.totalSeconds());

				// lerp between startSpeed and endSpeed with t.
				float variableSpeed = variableSpeedStartSpeed + (variableSpeedEndSpeed - variableSpeedStartSpeed) * t;
				return variableSpeed;
			}
		}
		else
		{
			return constantSpeed;
		}
	}
}

void Bas::Clock::update()
{
	static unsigned long previousMillis;

	unsigned long currentMillis = millis();
	long long millisSinceLastUpdate = (currentMillis - previousMillis) * getCurrentSpeed();
	previousMillis = currentMillis;

	static long long millisSinceLastSecond;
	millisSinceLastSecond += millisSinceLastUpdate;

	long long numSeconds = 0;

	if (millisSinceLastSecond >= numMillisecondsInSecond || millisSinceLastSecond <= 0-numMillisecondsInSecond)
	{
		numSeconds = floor(millisSinceLastSecond / numMillisecondsInSecond);
		millisSinceLastSecond = millisSinceLastSecond % numMillisecondsInSecond;
		
		TimeSpan timeToAdd{ abs(numSeconds) };
		if (constantSpeed < 0)
		{
			time = time - timeToAdd;
		}
		else
		{
			time = time + timeToAdd;
		}
	}

	/*Serial.print(time.hour());
	Serial.print(":");
	Serial.print(time.minute());
	Serial.print(":");
	Serial.println(time.second());*/
}
