// Hand.h

#ifndef _HAND_h
#define _HAND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "HandMotor.h"
#include "Clock.h"


namespace Bas
{
	class Hand
	{
	public:
		enum HandType { hour, minute };

	private:
		HandType type;
		float currentTime;
		HandMotor motor;
		Clock* clock;

	public:
		Hand(Clock* clock, const HandMotor& handMotor, HandType handType);
		void begin();
		void calibrate(int time);
		void update();
	};
}

#endif

