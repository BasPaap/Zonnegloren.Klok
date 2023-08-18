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
#include "NetworkInfo.h"

namespace Bas
{
	class WebServer
	{
	public:
		typedef enum { configurationPage, controlPage } page;
		static const int MAX_SCANNED_NETWORKS = 20;

	private:
		Configuration configuration;
		WiFiServer server{ 80 };
		page pageToServe;
		
		Bas::NetworkInfo scannedNetworks[MAX_SCANNED_NETWORKS];
		int scannedNetworksLength = 0;

		void printWiFiOption(WiFiClient* client, const char* ssid, int32_t rssi, Bas::NetworkInfo::encryptionType_t encryptionType);
	public:
		WebServer(Configuration configuration);
		void initialize();		
		void initialize(Bas::NetworkInfo* scannedNetworks, int scannedNetworksLength);
		void update();
		void setPageToServe(page pageToServe);
	};
}

#endif

