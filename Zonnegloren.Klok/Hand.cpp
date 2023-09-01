// 
// 
// 

#include "Hand.h"

Bas::Hand::Hand(Clock* clock, const HandMotor& handMotor, HandType handType) : clock(clock), motor(handMotor), type(handType)
{
}

void Bas::Hand::calibrate(int time)
{
	this->currentTime = time;
}

void Bas::Hand::begin()
{
	motor.begin();

	float otherTime;

	if (this->type == hour)
	{
		clock->getTime(&currentTime, &otherTime);
	}
	else
	{
		clock->getTime(&otherTime, &currentTime);
	}
}

void Bas::Hand::update()
{
	float newTime;
	float timeToIgnore;

	if (type == hour)
	{
		clock->getTime(&newTime, &timeToIgnore);
	} 
	else
	{
		clock->getTime(&timeToIgnore, &newTime);
	}

	float deltaTime;
	if (clock->getCurrentSpeed() < 0)
	{
		if (newTime <= currentTime)
		{
			deltaTime = newTime - currentTime;
		}
		else
		{
			deltaTime = (type == hour ? -12 : -60) - currentTime + newTime;
		}
	}
	else
	{
		if (newTime >= currentTime)
		{
			deltaTime = newTime - currentTime;
		}
		else
		{
			deltaTime = (type == hour ? 12 : 60) - currentTime + newTime;
		}
	}
		
	currentTime = newTime;
	float numRevolutions = deltaTime / (type == hour ? 12.0 : 60.0);

	motor.revolve(numRevolutions);
}