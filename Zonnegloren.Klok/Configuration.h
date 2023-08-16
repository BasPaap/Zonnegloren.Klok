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
		static const int MAX_SSID_LENGTH = 32;
		static const int MAX_PASSWORD_LENGTH = 63;
		static const int MAX_DOMAIN_NAME_LENGTH = 253;

		char ssid[MAX_SSID_LENGTH + 1];
		char password[MAX_PASSWORD_LENGTH + 1];
		char deviceDomainName[MAX_DOMAIN_NAME_LENGTH + 1];
		bool areValuesFound;
		bool readValue(int address, int maxLength, char* value);

	public:
		void initialize();
		bool isAvailable();
		void save();

		char* getSsid();
		void setSsid(const char* ssid);
		char* getPassword();
		void setPassword(const char* password);
		char* getDeviceDomainName();
		void setDeviceDomainNAme(const char* deviceDomainName);
	};
}

#endif

