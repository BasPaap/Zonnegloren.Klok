// 
// 
// 

#include "WiFiNetwork.h"

void Bas::WiFiNetwork::connectAsAccessPoint(const char* ssid)
{
	Serial.print("Starting access point ");
	Serial.println(ssid);
	
	wiFiStatus = WiFi.beginAP(ssid);
	isConnectedAsClient = false;	

	delay(2000);
}

void Bas::WiFiNetwork::connectAsClient(const char* ssid, const char* password)
{
	while (wiFiStatus != WL_CONNECTED)
	{
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);
		
		wiFiStatus = WiFi.begin(ssid, password); // Connect to WPA/WPA2 network.
		delay(2000); // wait 2 seconds for connection:
	}

	isConnectedAsClient = true;
}

bool Bas::WiFiNetwork::isClient()
{
	return isConnectedAsClient;
}

IPAddress Bas::WiFiNetwork::getLocalIPAddress()
{
	return WiFi.localIP();
}

void Bas::WiFiNetwork::update()
{
	if (wiFiStatus != WiFi.status())
	{
		wiFiStatus = WiFi.status();

		switch (wiFiStatus)
		{
		case WL_AP_CONNECTED:
			Serial.println("Device connected to Access Point.");
			break;		
		case WL_DISCONNECTED:
			Serial.println("Device disconnected from Access Point.");
			break;
		case WL_AP_LISTENING:
			Serial.println("Access point is listening.");
			break;
		default:
			break;
		}
	}
}

void Bas::WiFiNetwork::printWiFiClientStatus()
{
	Serial.print("Connected to SSID: ");
	Serial.println(WiFi.SSID());

	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("Signal strength (RSSI): ");
	Serial.print(rssi);
	Serial.println(" dBm");
}