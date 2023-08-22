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
		const int MAX_SSID_LENGTH = 32;
		const int MAX_PASSWORD_LENGTH = 63;
		const int MAX_DOMAIN_NAME_LENGTH = 253;
		const int MAX_ENCRYPTION_TYPE_CODE_LENGTH = 1;
		const int MAX_KEY_INDEX_LENGTH = 1;

		using ConfigurationDataReceivedCallbackPointer = void(*)(const char* ssid, const char* password, uint8_t keyIndex, const Bas::NetworkInfo::encryptionType_t encryptionType, const char* domainName);
		using ControlDataReceivedCallbackPointer = void(*)();
		using RequestResetCallbackPointer = void(*)();
		using CalibrationDataReceivedCallbackPointer = void(*)(uint8_t hours, uint8_t minutes);
	public:
		typedef enum { CONFIGURATION_PAGE, FIRST_CALIBRATION_PAGE, CONTROL_PAGE } page;
		typedef enum { UNKNOWN, GET, POST, PUT, PATCH, DELETE } httpMethod;
		static const int MAX_SCANNED_NETWORKS = 20;
		static const int MAX_BODY_LENGTH = 255;

	private:		
		WiFiServer server{ 80 };
		page pageToServe;
		
		Bas::NetworkInfo scannedNetworks[MAX_SCANNED_NETWORKS];
		int scannedNetworksLength = 0;
		ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback;
		ControlDataReceivedCallbackPointer onControlDataReceivedCallback;
		RequestResetCallbackPointer requestResetCallback;
		CalibrationDataReceivedCallbackPointer calibrationDataReceivedCallback;

		void printPageHeader(WiFiClient& client, const char* title);
		void printPageFooter(WiFiClient& client);
		void printWiFiOption(WiFiClient& client, const char* ssid, int32_t rssi, Bas::NetworkInfo::encryptionType_t encryptionType);
		void printConfigurationPage(WiFiClient& client);
		void printConfirmConfigurationPage(WiFiClient& client, const char* ssid, const char* domainName);
		void printFirstCalibrationPage(WiFiClient& client);
		void printControlPage(WiFiClient& client, IPAddress localIpAddress, uint8_t hours, uint8_t minutes, float speed, uint8_t startHours, uint8_t startMinutes, float startSpeed, uint8_t endHours, uint8_t endMinutes, float endSpeed);
		httpMethod getHttpMethod(WiFiClient& client);
		int getRequestBody(WiFiClient& client, char* body);
		void parseConfigurationData(char* body, char* ssid, char* password, char* domainName, Bas::NetworkInfo::encryptionType_t* encryptionType, uint8_t* keyIndex);
		bool startswith(const char* string, const char* prefix);
		void urlDecode(const char* input, char* output);
		unsigned char h2int(char c);

	public:
		WebServer();
		void begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, ControlDataReceivedCallbackPointer onControlDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback);
		void begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, ControlDataReceivedCallbackPointer onControlDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback, Bas::NetworkInfo* scannedNetworks, int scannedNetworksLength);
		void update();
		void setPageToServe(page pageToServe);
	};
}

#endif

