// SignalLed.h

#ifndef _SIGNALLED_h
#define _SIGNALLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Led.h"

namespace Bas
{
	class SignalLed : Led
	{
		unsigned long previousMillis{ 0 };
		unsigned long onInterval{ 0 };
		unsigned long offInterval{ 0 };
		bool isOn = false;
		bool isBlinking = false;

	public:
		SignalLed(int pin);

		void begin();
		void turnOn();
		void turnOff();
		void startBlinking(unsigned long interval);
		void startBlinking(unsigned long onInterval, unsigned long offInterval);
		void stopBlinking();
		void update();
	};
}

#endif

