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

void Bas::Clock::setVariableSpeed(int startHour, int startMinute, float startSpeed, int endHour, int endMinute, float endSpeed)
{
	this->variableSpeedStartHour = startHour;
	this->variableSpeedStartMinute = startMinute;
	this->variableSpeedStartSpeed = startSpeed;
	this->variableSpeedEndHour = endHour;
	this->variableSpeedEndMinute = endMinute;
	this->variableSpeedEndSpeed = endSpeed;
}

void Bas::Clock::getVariableSpeed(int* startHour, int* startMinute, float* startSpeed, int* endHour, int* endMinute, float* endSpeed)
{
	*startHour = this->variableSpeedStartHour;
	*startMinute = this->variableSpeedStartMinute;
	*startSpeed = this->variableSpeedStartSpeed;
	*endHour = this->variableSpeedEndHour;
	*endMinute = this->variableSpeedEndMinute;
	*endSpeed = this->variableSpeedEndSpeed;
}

void Bas::Clock::update()
{
	static unsigned long previousMillis;

	unsigned long currentMillis = millis();
	long long millisSinceLastUpdate = (currentMillis - previousMillis) * constantSpeed;
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
}
