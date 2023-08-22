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
			return UNKNOWN;
		}
	}

	return UNKNOWN;
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
				bodyLength = client.readBytes(body, MAX_BODY_LENGTH);				
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

void Bas::WebServer::parseConfigurationData(char* body, char* ssid, char* password, char* domainName, Bas::NetworkInfo::encryptionType_t* encryptionType, uint8_t* keyIndex)
{
	const char* SSID_TOKEN = "ssid=";
	const char* PASSWORD_TOKEN = "password=";
	const char* DOMAIN_NAME_TOKEN = "domainName=";
	const char* ENCRYPTION_TYPE_TOKEN = "encryption=";
	const char* KEY_INDEX_TOKEN = "keyIndex=";
	
	char encryptionTypeCode[MAX_ENCRYPTION_TYPE_CODE_LENGTH + 1];
	char keyIndexCode[MAX_KEY_INDEX_LENGTH + 1];

	char* token = strtok(body, "&");

	while (token != NULL)
	{
		if (startswith(token, SSID_TOKEN))
		{
			urlDecode(token + strlen(SSID_TOKEN), ssid);			
		}
		else if (startswith(token, PASSWORD_TOKEN))
		{
			urlDecode(token + strlen(PASSWORD_TOKEN), password);
		}
		else if (startswith(token, DOMAIN_NAME_TOKEN))
		{
			urlDecode(token + strlen(DOMAIN_NAME_TOKEN), domainName);			
		}
		else if (startswith(token, ENCRYPTION_TYPE_TOKEN))
		{
			urlDecode(token + strlen(ENCRYPTION_TYPE_TOKEN), encryptionTypeCode);
		}
		else if (startswith(token, KEY_INDEX_TOKEN))
		{
			urlDecode(token + strlen(KEY_INDEX_TOKEN), keyIndexCode);
		}

		token = strtok(NULL, "&");
	}

	*keyIndex = atoi(keyIndexCode);
	
	switch (atoi(encryptionTypeCode))
	{
	case 1:
		*encryptionType = Bas::NetworkInfo::WPA;
		break;
	case 2:
		*encryptionType = Bas::NetworkInfo::WEP;
		break;
	case 0:
	default:
		*encryptionType = Bas::NetworkInfo::NONE;
		break;
	}	
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
	this->calibrationDataReceivedCallback = onCalibrationDataReceivedCallback;
	
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
				
		char body[MAX_BODY_LENGTH + 1]{ 0 };
		int bodyLength = getRequestBody(client, body);
		
		Serial.println("Web server request received.");

		client.println("HTTP/1.1 200 OK");
		client.println("Content-type:text/html");
		client.println();
				
		switch (pageToServe)
		{
		case CONFIGURATION_PAGE:

			if (method == POST)
			{
				char ssid[MAX_SSID_LENGTH + 1];
				char password[MAX_PASSWORD_LENGTH + 1];
				char domainName[MAX_DOMAIN_NAME_LENGTH + 1];
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
		case FIRST_CALIBRATION_PAGE:
			if (method != POST)
			{
				printFirstCalibrationPage(client);
				break;
			}
			else
			{
				// TODO: get the calibration data from the POST request.
				calibrationDataReceivedCallback(0, 0);
				setPageToServe(CONTROL_PAGE); // Serve Control pages from now on.
				// NOTE: don't break here! We want it to fall through to CONTROL_PAGE.
			}			
		case CONTROL_PAGE:			
		default:
			printControlPage(client, IPAddress{ 127,0,0,1 }, 0, 0, 1, 0, 0, 1, 0, 0, 1);
			break;
		}

		client.println();
		client.stop();

		if (method == POST && pageToServe == CONFIGURATION_PAGE)
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
