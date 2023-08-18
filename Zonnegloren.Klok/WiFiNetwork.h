// WiFi.h

#ifndef _WIFI_h
#define _WIFI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<WiFiNINA.h>
#include "NetworkInfo.h"

namespace Bas
{
	class WiFiNetwork
	{	
		bool isConnectedAsClient = false;
		int wiFiStatus = WL_IDLE_STATUS;
		void printWiFiClientStatus();
	public:
		void connectAsAccessPoint(const char* ssid);
		void connectAsClient(const char* ssid, const char* password);		
		bool isClient();
		IPAddress getLocalIPAddress();
		void update();		
	};
}


#endif

