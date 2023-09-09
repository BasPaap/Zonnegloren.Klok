// 
// 
// 

#include "SignalLed.h"

Bas::SignalLed::SignalLed(int pin) : Led(pin)
{
}

void Bas::SignalLed::begin()
{
	previousMillis = millis();
	Led::begin();
}

void Bas::SignalLed::turnOn()
{
	isOn = true;
	Led::turnOn();
}

void Bas::SignalLed::turnOff()
{
	isOn = false;
	Led::turnOff();
}

void Bas::SignalLed::startBlinking(unsigned long interval)
{
	startBlinking(interval, interval);
}

void Bas::SignalLed::startBlinking(unsigned long onInterval, unsigned long offInterval)
{
	isBlinking = true;
	this->onInterval = onInterval;
	this->offInterval = offInterval;
}

void Bas::SignalLed::stopBlinking()
{
	isBlinking = false;
	turnOff();
}

void Bas::SignalLed::update()
{
	if (isBlinking)
	{
		unsigned long currentMillis = millis();

		if (isOn && currentMillis - previousMillis >= onInterval)
		{
			turnOff();
			previousMillis = currentMillis;
		}
		else if (!isOn && currentMillis - previousMillis >= offInterval)
		{
			turnOn();
			previousMillis = currentMillis;
		}
	}
}
