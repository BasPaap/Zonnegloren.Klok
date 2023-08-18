// 
// 
// 

#include "NetworkInfo.h"

Bas::NetworkInfo::NetworkInfo()
{
}

Bas::NetworkInfo::NetworkInfo(const char* ssid, int32_t rssi, uint8_t encryptionType) : rssi(rssi)
{
	strncpy(this->ssid, ssid, MAX_SSID_LENGTH);

	switch (encryptionType)
	{
	case 2:
	case 4:
		this->encryptionType = WPA;
		break;
	case 5:
		this->encryptionType = WEP;
		break;
	default:
		this->encryptionType = NONE;
			break;
	}
}
