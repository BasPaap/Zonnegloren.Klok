// 
// 
// 

#include "WiFiNetwork.h"

void Bas::WiFiNetwork::connectAsAccessPoint(const char* ssid)
{
	WiFi.beginAP(ssid);
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
}

IPAddress Bas::WiFiNetwork::getLocalIPAddress()
{
	return WiFi.localIP();
}

void Bas::WiFiNetwork::printWiFiStatus()
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