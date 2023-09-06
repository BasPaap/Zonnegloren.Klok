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
		else
		{
			return unknown;
		}
	}

	return unknown;
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

void Bas::WebServer::parseCalibrationData(char* body, uint8_t* hours, uint8_t* minutes)
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

void Bas::WebServer::begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, ControlDataReceivedCallbackPointer onControlDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback)
{
	this->onConfigurationDataReceivedCallback = onConfigurationDataReceivedCallback;
	this->onControlDataReceivedCallback = onControlDataReceivedCallback;
	this->requestResetCallback = requestResetCallback;
	this->onCalibrationDataReceivedCallback = onCalibrationDataReceivedCallback;
	
	server.begin();
}

void Bas::WebServer::begin(ConfigurationDataReceivedCallbackPointer onConfigurationDataReceivedCallback, ControlDataReceivedCallbackPointer onControlDataReceivedCallback, RequestResetCallbackPointer requestResetCallback, CalibrationDataReceivedCallbackPointer onCalibrationDataReceivedCallback, Bas::NetworkInfo* scannedNetworks, int scannedNetworksLength)
{
	this->scannedNetworksLength = scannedNetworksLength;
	for (size_t i = 0; i < this->scannedNetworksLength; i++)
	{
		this->scannedNetworks[i] = Bas::NetworkInfo{ scannedNetworks[i] };
	}

	begin(onConfigurationDataReceivedCallback, onControlDataReceivedCallback, requestResetCallback, onCalibrationDataReceivedCallback);
}

void Bas::WebServer::update()
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

				parseCalibrationData(body, &hours, &minutes);
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

			if (method == POST)
			{
				onControlDataReceivedCallback();
			}

			printControlPage(client, IPAddress{ 127,0,0,1 }, 0, 0, 1, 0, 0, 1, 0, 0, 1);
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
