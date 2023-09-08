// 
// 
// 

#include "WebServer.h"
#include "NetworkInfo.h"

Bas::WebServer::httpMethod Bas::WebServer::getHttpMethod(WiFiClient& client)
{
	if (client.available())
	{
		const int MAX_METHOD_LENGTH = 6;
		char method[MAX_METHOD_LENGTH + 1]{ 0 };
		int numBytesRead = client.readBytesUntil(' ', method, MAX_METHOD_LENGTH);

		if (strcmp("GET", method) == 0)
		{
			return GET;
		}
		else if (strcmp("POST", method) == 0)
		{
			return POST;
		}
		else if (strcmp("PUT", method) == 0)
		{
			return PUT;
		}
		else if (strcmp("PATCH", method) == 0)
		{
			return PATCH;
		}
		else if (strcmp("DELETE", method) == 0)
		{
			return POST;
		}
	}

	return unknownHttpMethod;
}

Bas::WebServer::controlFormType Bas::WebServer::getControlFormType(const char* body)
{
		if (strcmp("timeForm", body) == 0)
		{
			return controlFormType::time;
		}
		else if (strcmp("speedForm", body) == 0)
		{
			return controlFormType::constantSpeed;
		}
		else if (strcmp("variableSpeedForm", body) == 0)
		{
			return controlFormType::variableSpeed;
		}
		else if (strcmp("calibrationForm", body) == 0)
		{
			return controlFormType::calibration;
		}
		else
		{
			return unknownFormType;
		}

}

int Bas::WebServer::getRequestBody(WiFiClient& client, char* body)
{
	int bodyLength = 0;
	int lineLength = 0;

	while (client.connected() && client.available())
	{
		char character = client.read();

		if (character == '\r')
		{
			client.read(); // read the '\n' character that will follow '\r'
						
			if (lineLength == 0)
			{
				// All meta information for the request has been sent, so what will follow is the body.
				bodyLength = client.readBytes(body, maxBodyLength);				
			}

			lineLength = 0;			
		}
		else
		{
			lineLength++;
		}
	}

	return bodyLength;
}

void Bas::WebServer::parseTime(char* time, uint8_t* hours, uint8_t* minutes)
{
	const int maxHoursCharacters{ 2 };
	char hoursToken[maxHoursCharacters + 1];
	hoursToken[0] = time[0];
	hoursToken[1] = time[1];
	hoursToken[2] = 0;

	const int maxMinutesCharacters{ 2 };
	char minutesToken[maxMinutesCharacters + 1];
	minutesToken[0] = time[3];
	minutesToken[1] = time[4];
	minutesToken[2] = 0;

	*hours = atoi(hoursToken);
	*minutes = atoi(minutesToken);
}

void Bas::WebServer::parseConfigurationData(char* body, char* ssid, char* password, char* domainName, Bas::NetworkInfo::encryptionType_t* encryptionType, uint8_t* keyIndex)
{
	const char* ssidToken = "ssid=";
	const char* passwordToken = "password=";
	const char* domainNameToken = "domainName=";
	const char* encryptionTypeToken = "encryption=";
	const char* keyIndexToken = "keyIndex=";
	
	char encryptionTypeCode[maxEncryptionTypeCodeLength + 1];
	char keyIndexCode[maxKeyIndexLength + 1];

	char* token = strtok(body, "&");

	while (token != NULL)
	{
		if (startswith(token, ssidToken))
		{
			urlDecode(token + strlen(ssidToken), ssid);			
		}
		else if (startswith(token, passwordToken))
		{
			urlDecode(token + strlen(passwordToken), password);
		}
		else if (startswith(token, domainNameToken))
		{
			urlDecode(token + strlen(domainNameToken), domainName);			
		}
		else if (startswith(token, encryptionTypeToken))
		{
			urlDecode(token + strlen(encryptionTypeToken), encryptionTypeCode);
		}
		else if (startswith(token, keyIndexToken))
		{
			urlDecode(token + strlen(keyIndexToken), keyIndexCode);
		}

		token = strtok(NULL, "&");
	}

	*keyIndex = atoi(keyIndexCode);
	
	switch (atoi(encryptionTypeCode))
	{
	case 1:
		*encryptionType = Bas::NetworkInfo::wpa;
		break;
	case 2:
		*encryptionType = Bas::NetworkInfo::wep;
		break;
	case 0:
	default:
		*encryptionType = Bas::NetworkInfo::none;
		break;
	}	
}

void Bas::WebServer::parseTimeData(char* body, uint8_t* hours, uint8_t* minutes)
{
	const char* timeToken = "time=";
	char* token = strtok(body, "&");

	const int maxTimeCharacters{ 5 };
	char time[maxTimeCharacters + 1];

	while (token != NULL)
	{
		if (startswith(token, timeToken))
		{
			urlDecode(token + strlen(timeToken), time);
		}		

		token = strtok(NULL, "&");
	}

	parseTime(time, hours, minutes);
}

void Bas::WebServer::parseConstantSpeedData(char* body, float* constantSpeed)
{
	const char* speedToken = "speed=";
	char* token = strtok(body, "&");

	const int maxSpeedCharacters{ 10 };
	char speed[maxSpeedCharacters + 1];

	while (token != NULL)
	{
		if (startswith(token, speedToken))
		{
			urlDecode(token + strlen(speedToken), speed);
		}

		token = strtok(NULL, "&");
	}

	*speed = atof(speed);
}

void Bas::WebServer::parseVariableSpeedData(char* body, uint8_t* startHours, uint8_t* startMinutes, float* variableStartSpeed, uint8_t* endHours, uint8_t* endMinutes, float* variableEndSpeed)
{
	const char* startTimeToken = "startTime=";
	const char* startSpeedToken = "startSpeed=";
	const char* endTimeToken = "endTime=";
	const char* endSpeedToken = "endSpeed=";
		
	const int maxTimeCharacters{ 5 };
	char startTime[maxTimeCharacters + 1];
	char endTime[maxTimeCharacters + 1];
	const int maxSpeedCharacters{ 10 };
	char startSpeed[maxSpeedCharacters + 1];
	char endSpeed[maxSpeedCharacters + 1];

	char* token = strtok(body, "&");

	while (token != NULL)
	{
		if (startswith(token, startTimeToken))
		{
			urlDecode(token + strlen(startTimeToken), startTime);
		}
		else if (startswith(token, startSpeedToken))
		{
			urlDecode(token + strlen(startSpeedToken), startSpeed);
		}
		else if (startswith(token, endTimeToken))
		{
			urlDecode(token + strlen(endTimeToken), endTime);
		}
		else if (startswith(token, endSpeedToken))
		{
			urlDecode(token + strlen(endSpeedToken), endSpeed);
		}

		token = strtok(NULL, "&");
	}

	parseTime(startTime, startHours, startMinutes);
	*variableStartSpeed = atof(startSpeed);
	parseTime(endTime, endHours, endMinutes);
	*variableEndSpeed = atof(endSpeed);
}

void Bas::WebServer::urlDecode(const char* input, char* output)
{	
	char c;
	char code0;
	char code1;
	int outputLength = 0;

	for (int i = 0; i < strlen(input); i++) 
	{
		c = input[i];
		if (c == '+') {
			output[outputLength++] = ' ';
		}
		else if (c == '%') 
		{
			code0 = input[++i];
			code1 = input[++i];
			c = (h2int(code0) << 4) | h2int(code1);
			output[outputLength++] = c;
		}
		else 
		{
			output[outputLength++] = c;
		}

		//yield();
	}

	output[outputLength] = 0;
}

unsigned char Bas::WebServer::h2int(char c)
{
	if (c >= '0' && c <= '9') 
	{
		return((unsigned char)c - '0');
	}
	if (c >= 'a' && c <= 'f') 
	{
		return((unsigned char)c - 'a' + 10);
	}
	if (c >= 'A' && c <= 'F') 
	{
		return((unsigned char)c - 'A' + 10);
	}

	return(0);
}

bool Bas::WebServer::startswith(const char* string, const char* prefix)
{
	while (*prefix)
	{
		if (*prefix++ != *string++)
			return false;
	}

	return true;
}

Bas::WebServer::WebServer()
{
}

void Bas::WebServer::begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback)
{
	this->onConfigurationDataReceivedCallback = onConfigurationDataReceivedCallback;
	this->requestResetCallback = requestResetCallback;
	this->onCalibrationDataReceivedCallback = onCalibrationDataReceivedCallback;
	
	server.begin();
}

void Bas::WebServer::begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback, Bas::NetworkInfo* scannedNetworks, int scannedNetworksLength)
{
	this->scannedNetworksLength = scannedNetworksLength;
	for (size_t i = 0; i < this->scannedNetworksLength; i++)
	{
		this->scannedNetworks[i] = Bas::NetworkInfo{ scannedNetworks[i] };
	}

	begin(onConfigurationDataReceivedCallback, requestResetCallback, onCalibrationDataReceivedCallback);
}

void Bas::WebServer::update(IPAddress localIPAddress, uint8_t currentHours, uint8_t currentMinutes, float constantSpeed, uint8_t startHours, uint8_t startMinutes, float variableStartSpeed, uint8_t endHours, uint8_t endMinutes, float variableEndSpeed)
{
	if (!server.status())
	{		
		server.begin();
	}

	WiFiClient client = server.available();
	if (client)
	{
		httpMethod method = getHttpMethod(client);
				
		char body[maxBodyLength + 1]{ 0 };
		int bodyLength = getRequestBody(client, body);
		
		Serial.println("Web server request received.");

		client.println("HTTP/1.1 200 OK");
		client.println("Content-type:text/html");
		client.println();
				
		switch (pageToServe)
		{
		case configurationPage:

			if (method == POST)
			{
				char ssid[maxSsidLength + 1];
				char password[maxPasswordLength + 1];
				char domainName[maxDomainNameLength + 1];
				Bas::NetworkInfo::encryptionType_t encryptionType;
				uint8_t keyIndex;
				
				parseConfigurationData(body, ssid, password, domainName, &encryptionType, &keyIndex);
				printConfirmConfigurationPage(client, ssid, domainName);
				this->onConfigurationDataReceivedCallback(ssid, password, keyIndex, encryptionType, strlwr(domainName));
			}
			else
			{
				printConfigurationPage(client);
			}
			break;
		case firstCalibrationPage:
			if (method == POST)
			{
				uint8_t hours;
				uint8_t minutes;

				parseTimeData(body, &hours, &minutes);
				this->onCalibrationDataReceivedCallback(hours, minutes);
				setPageToServe(controlPage); // Serve Control pages from now on.
				printControlPage(client, IPAddress{ 127,0,0,1 }, hours, minutes, 1, 0, 0, 1, 0, 0, 1);
				break;
			}
			else
			{	
				printFirstCalibrationPage(client);
				break;				
			}			
		case controlPage:			
		default:
			uint8_t calibrationHours{ 0 };
			uint8_t calibrationMinutes{ 0 };

			if (method == POST)
			{				
				controlFormType formType = getControlFormType(body);

				switch (formType)
				{
				case controlFormType::time:
					parseTimeData(body, &currentHours, &currentMinutes);
					break;
				case controlFormType::constantSpeed:
					parseConstantSpeedData(body, &constantSpeed);
					break;
				case controlFormType::variableSpeed:
					parseVariableSpeedData(body, &startHours, &startMinutes, &variableStartSpeed, &endHours, &endMinutes, &variableEndSpeed);
					break;
				case controlFormType::calibration:
					parseTimeData(body, &calibrationHours, &calibrationMinutes);
					onCalibrationDataReceivedCallback(calibrationHours, calibrationMinutes);
					break;
				case unknownFormType:
				default:
					break;
				}				
			}

			printControlPage(client, localIPAddress, currentHours, currentMinutes, constantSpeed, startHours, startMinutes, variableStartSpeed, endHours, endMinutes, variableEndSpeed);
			break;
		}

		client.println();
		client.stop();

		if (method == POST && pageToServe == configurationPage)
		{
			// Configuration data has been posted so we need to reset the arduino.
			requestResetCallback();
		}
	}
}

void Bas::WebServer::setPageToServe(page pageToServe)
{
	this->pageToServe = pageToServe;
}
