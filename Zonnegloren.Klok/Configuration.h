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
		static const int MAX_KEY_INDEX_LENGTH = 1;
		static const int MAX_ENCRYPTION_TYPE_LENGTH = 1;

		static const char HASH_VALUE = 'B';

		char ssid[MAX_SSID_LENGTH + 1];
		char password[MAX_PASSWORD_LENGTH + 1];
		char deviceDomainName[MAX_DOMAIN_NAME_LENGTH + 1];
		Bas::NetworkInfo::encryptionType_t encryptionType;
		int8_t keyIndex;

		bool areValuesFound;
		bool readValue(int address, int maxLength, char* value);
		void writeValue(int address, char* value);
		void writeValue(int address, char* value, size_t length);
		uint8_t hash(uint8_t value, int salt);
		void resetArduino();

	public:
		void initialize();
		bool isAvailable();
		void save();
		void reset();

		char* getSsid();
		void setSsid(const char* ssid);
		char* getPassword();
		void setPassword(const char* password);
		char* getDeviceDomainName();
		void setDeviceDomainName(const char* deviceDomainName);
		int8_t getKeyIndex();
		void setKeyIndex(int8_t keyIndex);
		Bas::NetworkInfo::encryptionType_t getEncryptionType();
		void setEncryptionType(Bas::NetworkInfo::encryptionType_t encryptionType);
	};
}

#endif

