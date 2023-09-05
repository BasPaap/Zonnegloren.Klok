// 
// 
// 

#include "NetworkInfo.h"

Bas::NetworkInfo::NetworkInfo()
{
}

Bas::NetworkInfo::NetworkInfo(const char* ssid, int32_t rssi, uint8_t encryptionType) : rssi(rssi)
{
	strncpy(this->ssid, ssid, maxSsidLength);

	switch (encryptionType)
	{
	case 2:
	case 4:
		this->encryptionType = wpa;
		break;
	case 5:
		this->encryptionType = wep;
		break;
	default:
		this->encryptionType = none;
			break;
	}
}
