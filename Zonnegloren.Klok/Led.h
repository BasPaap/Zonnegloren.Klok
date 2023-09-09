// Led.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Bas
{
	class Led
	{
		int pin{ LED_BUILTIN };
	public:
		Led(int pin);
		void begin();

		void turnOn();
		void turnOff();
	};
}

#endif

