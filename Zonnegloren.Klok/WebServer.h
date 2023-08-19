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
		typedef enum { CONFIGURATION_PAGE, CONTROL_PAGE } page;
		typedef enum { UNKNOWN, GET, POST, PUT, PATCH, DELETE } httpMethod;
		static const int MAX_SCANNED_NETWORKS = 20;
		static const int MAX_BODY_LENGTH = 255;

	private:		
		WiFiServer server{ 80 };
		page pageToServe;
		
		Bas::NetworkInfo scannedNetworks[MAX_SCANNED_NETWORKS];
		int scannedNetworksLength = 0;

		void printWiFiOption(WiFiClient& client, const char* ssid, int32_t rssi, Bas::NetworkInfo::encryptionType_t encryptionType);
		httpMethod getHttpMethod(WiFiClient& client);
		int getRequestBody(WiFiClient& client, char* body);
		void parseConfigurationBody(char* body);
		bool startswith(const char* string, const char* prefix);
		void urlDecode(const char* input, char* output);
		unsigned char h2int(char c);
	public:
		WebServer();
		void initialize();		
		void initialize(Bas::NetworkInfo* scannedNetworks, int scannedNetworksLength);
		void update();
		void setPageToServe(page pageToServe);
	};
}

#endif

