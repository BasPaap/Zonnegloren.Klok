// 
// 
// 

#include "Clock.h"
#include "TimeSpan.h"

long Bas::Clock::mod(long a, long n)
{
	return a < 0 ? ((a + 1) % n) + n - 1 : a % n;
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
	time = DateTime{ 2050, 7, 7, hour, minute, 0 };
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
	unsigned long millisSinceLastUpdate = (currentMillis - previousMillis) * constantSpeed;
	previousMillis = currentMillis;

	static unsigned long millisSinceLastSecond;
	millisSinceLastSecond += millisSinceLastUpdate;

	if (millisSinceLastSecond >= NUM_MILLISECONDS_IN_SECOND)
	{
		unsigned long numSeconds = floor(millisSinceLastSecond / NUM_MILLISECONDS_IN_SECOND);
		millisSinceLastSecond = mod(millisSinceLastSecond, NUM_MILLISECONDS_IN_SECOND);

		TimeSpan timeToAdd{ abs(numSeconds) };
		if (constantSpeed < 0)
		{
			time = time - timeToAdd;
		}
		else
		{
			time = time + timeToAdd;
		}

		time = DateTime{ 2050, 7, 7, time.hour(), time.minute(), numSeconds };
	}

	Serial.print(time.hour());
	Serial.print(":");
	Serial.print(time.minute());
	Serial.print(":");
	Serial.print(time.second());
	Serial.print(".");
	Serial.println(millisSinceLastSecond);
}
