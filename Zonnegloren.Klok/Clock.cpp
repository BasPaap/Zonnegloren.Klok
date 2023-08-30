// 
// 
// 

#include "Clock.h"
#include "TimeSpan.h"

float Bas::Clock::currentSpeed()
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
			Time variableSpeedEndTime = variableSpeedStartTime + variableSpeedDuration;

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

Bas::Clock::Clock()
{
}

void Bas::Clock::begin()
{
}

void Bas::Clock::setTime(int hour, int minute)
{
	// We'll consider the stepper motor's current positions to be the positions for currentHour and currentMinute.
	// Therefore, we need to calculate the amount of steps we need to move each hand from currentHour to hour and from currentMinute to minute.
	time = Time{ hour, minute };
}

void Bas::Clock::getTime(int* hour, int* minute)
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

void Bas::Clock::setVariableSpeed(int startHour, int startMinute, int durationInMinutes, float startSpeed, float endSpeed)
{
	this->variableSpeedStartTime = Time(startHour, startMinute);
	this->variableSpeedDuration = TimeSpan(durationInMinutes * 60);
	this->variableSpeedStartSpeed = startSpeed;
	this->variableSpeedEndSpeed = endSpeed;
}

void Bas::Clock::getVariableSpeed(int* startHour, int* startMinute, int* durationInMinutes, float* startSpeed, float* endSpeed)
{
	*startHour = this->variableSpeedStartTime.hour();
	*startMinute = this->variableSpeedStartTime.minute();
	*durationInMinutes = this->variableSpeedDuration.totalseconds();
	*startSpeed = this->variableSpeedStartSpeed;
	*endSpeed = this->variableSpeedEndSpeed;
}

void Bas::Clock::update()
{
	static unsigned long previousMillis;

	unsigned long currentMillis = millis();
	long long millisSinceLastUpdate = (currentMillis - previousMillis) * currentSpeed();
	previousMillis = currentMillis;

	static long long millisSinceLastSecond;
	millisSinceLastSecond += millisSinceLastUpdate;

	long long numSeconds = 0;

	if (millisSinceLastSecond >= NUM_MILLISECONDS_IN_SECOND || millisSinceLastSecond <= 0-NUM_MILLISECONDS_IN_SECOND)
	{
		numSeconds = floor(millisSinceLastSecond / NUM_MILLISECONDS_IN_SECOND);
		millisSinceLastSecond = millisSinceLastSecond % NUM_MILLISECONDS_IN_SECOND;
		
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

	Serial.print(time.hour());
	Serial.print(":");
	Serial.print(time.minute());
	Serial.print(":");
	Serial.println(time.second());
}
