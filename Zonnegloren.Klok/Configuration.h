// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "NetworkInfo.h"

namespace Bas
{
	class Configuration
	{
		static const int maxSsidLength = 32;
		static const int maxPasswordLength = 63;
		static const int maxDomainNameLength = 253;
		static const int maxKeyIndexLength = 1;
		static const int maxEncryptionTypeLength = 1;

		static const char hashValue = 'B';
		const char* domainNameTld = ".local";

		char ssid[maxSsidLength + 1];
		char password[maxPasswordLength + 1];
		char deviceDomainName[maxDomainNameLength + 1];
		Bas::NetworkInfo::encryptionType_t encryptionType;
		uint8_t keyIndex;

		bool areValuesFound;
		bool readValue(int address, int maxLength, char* value);
		void writeValue(int address, char* value);
		void writeValue(int address, char* value, size_t length);
		uint8_t hash(uint8_t value, int salt);

	public:
		void begin();
		bool isAvailable();
		void save();
		void clear();

		char* getSsid();
		void setSsid(const char* ssid);
		char* getPassword();
		void setPassword(const char* password);
		char* getDeviceDomainName();
		void setDeviceDomainName(const char* deviceDomainName);
		uint8_t getKeyIndex();
		void setKeyIndex(uint8_t keyIndex);
		Bas::NetworkInfo::encryptionType_t getEncryptionType();
		void setEncryptionType(Bas::NetworkInfo::encryptionType_t encryptionType);
	};
}

#endif

