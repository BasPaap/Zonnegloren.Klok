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

Bas::WebServer::WebServer(Configuration configuration) : configuration(configuration)
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

	//Serial.println(server.status());

	WiFiClient client = server.available();
	if (client)
	{
		Serial.println("Web server request received.");

		client.println("HTTP/1.1 200 OK");
		client.println("Content-type:text/html");
		client.println();

		switch (pageToServe)
		{
		case Bas::WebServer::page::configurationPage:
			
			client.print(config_html1); 			
			
			for (size_t i = 0; i < scannedNetworksLength; i++)
			{
				printWiFiOption(&client, scannedNetworks[i].ssid, scannedNetworks[i].rssi, scannedNetworks[i].encryptionType);
			}

			client.print(config_html2);
			break;
		case Bas::WebServer::page::controlPage:
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
