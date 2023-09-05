// 
// 
// 

#include "WiFiNetwork.h"

void Bas::WiFiNetwork::connectAsAccessPoint(const char* ssid)
{
	Serial.print("Starting access point ");
	Serial.println(ssid);
	
	WiFi.config(IPAddress(192, 168, 0, 1));
	wiFiStatus = WiFi.beginAP(ssid);
	isConnectedAsClient = false;	

	delay(2000);
}

void Bas::WiFiNetwork::connectAsClient(const char* ssid, const char* password, uint8_t keyIndex, Bas::NetworkInfo::encryptionType_t encryptionType, CallbackPointer onConnectionFailureCallback)
{
	const int MAX_ATTEMPTS = 10;
	int numAttempts = 0;

	while (wiFiStatus != WL_CONNECTED && numAttempts < MAX_ATTEMPTS)
	{
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);
		
		switch (encryptionType)
		{
		case Bas::NetworkInfo::wpa:
			wiFiStatus = WiFi.begin(ssid, password); // Connect to WPA/WPA2 network.
			break;
		case Bas::NetworkInfo::wep:
			wiFiStatus = WiFi.begin(ssid, keyIndex, password); // Connect to WEP network.
			break;
		case Bas::NetworkInfo::none:
		default:
			wiFiStatus = WiFi.begin(ssid); // Connect to public network
			break;
		}
		
		delay(2000); // wait 2 seconds for connection:

		numAttempts++;
	}

	if (wiFiStatus == WL_CONNECTED)
	{
		isConnectedAsClient = true;
		return;
	}
	else
	{
		onConnectionFailureCallback();
	}
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
			Serial.print("Wifi status: ");
			Serial.println(wiFiStatus);
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