// 
// 
// 

#include "Clock.h"

int Bas::Clock::mod(int a, int n)
{
	return a < 0 ? ((a + 1) % n) + n - 1 : a % n;
}

void Bas::Clock::getNewTime(int& newHour, int& newMinute, int& newSecond, int& newMillisecond)
{
	newHour = this->currentHour;
	newMinute = this->currentMinute;
	newSecond = this->currentSecond;
	newMillisecond = this->currentMillisecond;

	int elapsedMillisSinceLastLoop = millis() - lastMillis;
	lastMillis = millis();
	int deltaMillis = elapsedMillisSinceLastLoop * this->constantSpeed;

	newMillisecond += deltaMillis;
	if (newMillisecond < 0)
	{
		newSecond--;			// Dit gaat niet goed: bij hoge snelheden moet dit meer dan 1 seconde zijn.
	}
	else if (newMillisecond >= TOTAL_MILLISECONDS)
	{
		newSecond++;
	}

	if (newSecond < 0)
	{
		newMinute;
	}
	else if (newSecond >= TOTAL_SECONDS)
	{
		newMinute++;
	}

	if (newMinute < 0)
	{
		newHour--;
	}
	else if (newMinute > TOTAL_MINUTES)
	{
		newHour++;
	}

	newMillisecond = mod(newMillisecond, TOTAL_MILLISECONDS);
	newSecond = mod(newSecond, TOTAL_SECONDS);
	newMinute = mod(newMinute, TOTAL_MINUTES);
	newHour = mod(newHour, TOTAL_HOURS);
}

Bas::Clock::Clock()
{
}

void Bas::Clock::begin()
{
}

void Bas::Clock::calibrate(int currentlyDisplayedHour, int currentlyDisplayedMinute)
{
	this->currentHour = currentlyDisplayedHour;
	this->currentMinute = currentlyDisplayedMinute;
	this->currentSecond = 0;
}

void Bas::Clock::setTime(int hour, int minute)
{
	// We'll consider the stepper motor's current positions to be the positions for currentHour and currentMinute.
	// Therefore, we need to calculate the amount of steps we need to move each hand from currentHour to hour and from currentMinute to minute.

	this->currentHour = hour;
	this->currentMinute = minute;
	this->currentSecond = 0;
	this->currentMillisecond = 0;
}

void Bas::Clock::getTime(int* hour, int* minute)
{
	*hour = this->currentHour;
	*minute = this->currentMinute;
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
	int newHour, newMinute, newSecond, newMillisecond;
	getNewTime(newHour, newMinute, newSecond, newMillisecond);

	int hourDifference = newHour - currentHour;
	int minuteDifference = newMinute - currentMinute;
	int secondDifference = newSecond - currentSecond;

	numHourStepsToTake += NUM_STEPS_PER_HOUR * (hourDifference + (minuteDifference / (float)TOTAL_MINUTES));
	numMinuteStepsToTake += NUM_STEPS_PER_MINUTE * (minuteDifference + (secondDifference / (float)TOTAL_SECONDS));

	if (numHourStepsToTake >= 1.0)
	{
		/*Serial.print("Taking ");
		Serial.print(floor(numHourStepsToTake));
		Serial.print(" steps for hour.");*/
		numHourStepsToTake -= floor(numHourStepsToTake);
	}

	if (numMinuteStepsToTake >= 1.0)
	{
		/*Serial.print("Taking ");
		Serial.print(floor(numMinuteStepsToTake));
		Serial.print(" steps for minute.");*/
		numMinuteStepsToTake -= floor(numMinuteStepsToTake);
	}

	this->currentHour = newHour;
	this->currentMinute = newMinute;
	this->currentSecond = newSecond;
	this->currentMillisecond = newMillisecond;

	Serial.print(currentHour);
	Serial.print(":");
	Serial.print(currentMinute);
	Serial.print(":");
	Serial.print(currentSecond);
	Serial.print(":");
	Serial.print(currentMillisecond);
	Serial.print("\t\t");
	Serial.print(numHourStepsToTake, 5);
	Serial.print(" ");
	Serial.println(numMinuteStepsToTake, 5);
}
