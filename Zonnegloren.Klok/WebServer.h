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
		const int maxSsidLength = 32;
		const int maxPasswordLength = 63;
		const int maxDomainNameLength = 253;
		const int maxEncryptionTypeCodeLength = 1;
		const int maxKeyIndexLength = 1;

		using ConfigurationDataReceivedCallbackPointer = void(*)(const char* ssid, const char* password, uint8_t keyIndex, const Bas::NetworkInfo::encryptionType_t encryptionType, const char* domainName);
		using RequestResetCallbackPointer = void(*)();
		using CalibrationDataReceivedCallbackPointer = void(*)(uint8_t hours, uint8_t minutes);
		
	public:
		enum page { configurationPage, firstCalibrationPage, controlPage };
		enum httpMethod { unknownHttpMethod, GET, POST, PUT, PATCH, DELETE };
		
		static const int maxScannedNetworks = 20;
		static const int maxBodyLength = 255;

	private:		
		WiFiServer server{ 80 };
		page pageToServe;

		enum controlFormType { unknownFormType, time, constantSpeed, variableSpeed, calibration };
		
		Bas::NetworkInfo scannedNetworks[maxScannedNetworks];
		int scannedNetworksLength = 0;
		ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback;
		RequestResetCallbackPointer requestResetCallback;
		CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback;

		controlFormType getControlFormType(const char* body);
		void printPageHeader(WiFiClient& client, const char* title);
		void printPageFooter(WiFiClient& client);
		void printWiFiOption(WiFiClient& client, const char* ssid, int32_t rssi, Bas::NetworkInfo::encryptionType_t encryptionType);
		void printConfigurationPage(WiFiClient& client);
		void printConfirmConfigurationPage(WiFiClient& client, const char* ssid, const char* domainName);
		void printFirstCalibrationPage(WiFiClient& client);
		void printControlPage(WiFiClient& client, IPAddress localIpAddress, uint8_t hours, uint8_t minutes, float constantSpeed, uint8_t startHours, uint8_t startMinutes, float variableStartSpeed, uint8_t endHours, uint8_t endMinutes, float variableEndSpeed);
		httpMethod getHttpMethod(WiFiClient& client);
		int getRequestBody(WiFiClient& client, char* body);
		void parseTime(char* time, uint8_t* hours, uint8_t* minutes);
		void parseConfigurationData(char* body, char* ssid, char* password, char* domainName, Bas::NetworkInfo::encryptionType_t* encryptionType, uint8_t* keyIndex);
		void parseTimeData(char* body, uint8_t* hours, uint8_t* minutes);
		void parseConstantSpeedData(char* body, float* constantSpeed);
		void parseVariableSpeedData(char* body, uint8_t* startHours, uint8_t* startMinutes, float* variableStartSpeed, uint8_t* endHours, uint8_t* endMinutes, float* variableEndSpeed);
		bool startswith(const char* string, const char* prefix);
		void urlDecode(const char* input, char* output);
		unsigned char h2int(char c);

	public:
		WebServer();
		void begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback);
		void begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback, Bas::NetworkInfo* scannedNetworks, int scannedNetworksLength);
		void update(IPAddress localIPAddress, uint8_t currentHours, uint8_t currentMinutes, float constantSpeed, uint8_t startHours, uint8_t startMinutes, float variableStartSpeed, uint8_t endHours, uint8_t endMinutes, float variableEndSpeed);
		void setPageToServe(page pageToServe);
	};
}

#endif

