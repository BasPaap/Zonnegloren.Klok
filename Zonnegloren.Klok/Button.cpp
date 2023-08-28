/*
  Button.h - Library for a debounced button that can call calllbacks on rising or falling action.
  Created by Bas Paap, August 2023.
  Released into the public domain.
*/

#include "Button.h"

namespace Bas
{
	Button::Button(int pin, unsigned long debounceDelay, LogLevel logLevel = LogLevel::none) : pin{ pin }, debounceDelay{ debounceDelay }, risingCallback{ NULL }, fallingCallback{ NULL }, logLevel { logLevel }
	{
	}

	void Button::begin(CallbackPointer fallingCallback)
	{
		this->begin(fallingCallback, NULL);
	}

	void Button::begin(CallbackPointer fallingCallback, CallbackPointer risingCallback)
	{
		if (this->logLevel == LogLevel::normal)
		{
			Serial.print("Initializing button on pin ");
			Serial.println(this->pin);
		}

		this->risingCallback = risingCallback;
		this->fallingCallback = fallingCallback;
		pinMode(this->pin, INPUT_PULLUP);
	}

	void Button::update()
	{
		int currentButtonState = digitalRead(this->pin);
		unsigned long now = millis();

		if (currentButtonState != this->lastDebouncedButtonState)
		{
			if (now - this->lastDebounceTime > this->debounceDelay)
			{
				// A debounced button change has occurred!
				this->lastDebounceTime = now;
				this->lastDebouncedButtonState = currentButtonState;
				this->debouncedState = currentButtonState;

				// Call the appropriate callback function
				if (this->risingCallback != NULL && currentButtonState == HIGH)
				{
					if (this->logLevel == LogLevel::normal)
					{
						Serial.println("Button debounced on HIGH.");
					}

					this->risingCallback();
				}

				if (this->fallingCallback != NULL && currentButtonState == LOW)
				{
					if (this->logLevel == LogLevel::normal)
					{
						Serial.println("Button debounced on LOW.");
					}

					this->fallingCallback();
				}
			}
		}
	}
}
