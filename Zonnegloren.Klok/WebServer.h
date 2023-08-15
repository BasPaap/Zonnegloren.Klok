// WebServer.h

#ifndef _WEBSERVER_h
#define _WEBSERVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<WiFiNINA.h>
#include "Configuration.h"

namespace Bas
{
	class WebServer
	{
		Configuration configuration;
		WiFiServer server{ 80 };
	public:
		WebServer(Configuration configuration);
		void initialize();
		void update();
	};
}

#endif

