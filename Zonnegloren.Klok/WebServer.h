// WebServer.h

#ifndef _WEBSERVER_h
#define _WEBSERVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<WiFiNINA.h>

namespace Bas
{
	class WebServer
	{
		WiFiServer server{ 80 };
	public:
		void initialize();
		void update();
	};
}

#endif

