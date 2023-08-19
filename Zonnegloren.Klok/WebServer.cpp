// 
// 
// 

#include "WebServer.h"
#include "Config-HTML.h"
#include "NetworkInfo.h"

void Bas::WebServer::printWiFiOption(WiFiClient* client, const char* ssid, int32_t rssi, Bas::NetworkInfo::encryptionType_t encryptionType)
{
	client->print("<option value=\"");
	client->print(ssid);
	client->print("\" data-encryption=\"");

	switch (encryptionType)
	{
	case Bas::NetworkInfo::encryptionType_t::WPA:
		client->print("WPA");
		break;
	case Bas::NetworkInfo::encryptionType_t::WEP:
		client->print("WEP");
		break;
	case Bas::NetworkInfo::encryptionType_t::NONE:
	default:
		client->print("none");
		break;
	}

	client->print("\">");
	client->print(ssid);
	client->print(" (");

	switch (encryptionType)
	{
	case Bas::NetworkInfo::encryptionType_t::WPA:
		client->print("WPA");
		break;
	case Bas::NetworkInfo::encryptionType_t::WEP:
		client->print("WEP");
		break;
	case Bas::NetworkInfo::encryptionType_t::NONE:
	default:
		client->print("public");
		break;
	}

	client->print(")</option>");
}

Bas::WebServer::httpMethod Bas::WebServer::getHttpMethod(WiFiClient* client)
{
	if (client->available())
	{
		const int MAX_METHOD_LENGTH = 6;
		char method[MAX_METHOD_LENGTH + 1]{ 0 };
		int numBytesRead = client->readBytesUntil(' ', method, MAX_METHOD_LENGTH);

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

int Bas::WebServer::getRequestBody(WiFiClient* client, char* body)
{
	int bodyLength = 0;
	int lineLength = 0;

	while (client->connected() && client->available())
	{
		char character = client->read();

		if (character == '\r')
		{
			client->read(); // read the '\n' character that will follow '\r'
						
			if (lineLength == 0)
			{
				// All meta information for the request has been sent, so what will follow is the body.
				bodyLength = client->readBytes(body, MAX_BODY_LENGTH);				
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

Bas::WebServer::WebServer()
{
}

void Bas::WebServer::initialize()
{
	server.begin();
}

void Bas::WebServer::initialize(Bas::NetworkInfo* scannedNetworks, int scannedNetworksLength)
{
	this->scannedNetworksLength = scannedNetworksLength;
	for (size_t i = 0; i < this->scannedNetworksLength; i++)
	{
		this->scannedNetworks[i] = Bas::NetworkInfo{ scannedNetworks[i] };
	}
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
		httpMethod method = getHttpMethod(&client);
				
		char body[MAX_BODY_LENGTH + 1]{ 0 };
		int bodyLength = getRequestBody(&client, body);
		
		Serial.println("Web server request received.");

		client.println("HTTP/1.1 200 OK");
		client.println("Content-type:text/html");
		client.println();

		switch (pageToServe)
		{
		case Bas::WebServer::page::CONFIGURATION_PAGE:

			if (method == POST)
			{

			}
			else
			{
				client.print(config_html1);

				for (size_t i = 0; i < scannedNetworksLength; i++)
				{
					printWiFiOption(&client, scannedNetworks[i].ssid, scannedNetworks[i].rssi, scannedNetworks[i].encryptionType);
				}

				client.print(config_html2);
			}
			break;
		case Bas::WebServer::page::CONTROL_PAGE:
		default:
			client.print("hello world");
			break;
		}

		client.println();
		client.stop();
	}
}

void Bas::WebServer::setPageToServe(page pageToServe)
{
	this->pageToServe = pageToServe;
}
