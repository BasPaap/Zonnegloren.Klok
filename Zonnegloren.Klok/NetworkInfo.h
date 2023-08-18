// NetworkInfo.h

#ifndef _NETWORKINFO_h
#define _NETWORKINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Bas
{
	class NetworkInfo
	{
	public:
		static const int MAX_SSID_LENGTH = 32;
		typedef enum { WPA, WEP, NONE } encryptionType_t;
		NetworkInfo();
		NetworkInfo(const char* ssid, int32_t rssi, uint8_t encryptionType);
		char ssid[MAX_SSID_LENGTH +1];
		int32_t rssi;
		encryptionType_t encryptionType;

	};
}

#endif