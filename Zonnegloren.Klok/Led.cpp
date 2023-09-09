#include "Led.h"

Bas::Led::Led(int pin) : pin(pin)
{
}

void Bas::Led::begin()
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

void Bas::Led::turnOn()
{
	digitalWrite(pin, HIGH);
}

void Bas::Led::turnOff()
{
	digitalWrite(pin, LOW);
}

