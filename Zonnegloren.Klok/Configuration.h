// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Bas
{
	class Configuration
	{
		char* ssid;
		char* password;
		char* deviceDomainName;
	public:
		void initialize();
		bool isAvailable();
		void save();

		char* getSsid();
		void setSsid(char* ssid);
		char* getPassword();
		void setPassword(char* password);
		char* getDeviceDomainName();
		void setDeviceDomainNAme(char* deviceDomainName);
	};
}

#endif

