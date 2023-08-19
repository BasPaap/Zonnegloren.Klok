
#include <SPI.h>
#include "NetworkInfo.h"
#include <WiFiNINA.h>
#include "WiFiNetwork.h"
#include "Mdns.h"
#include "WebServer.h"
#include "Configuration.h"

Bas::Configuration configuration;
Bas::WiFiNetwork wiFiNetwork;
Bas::Mdns mdns;
Bas::WebServer webServer;

void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial);  // wait for serial port to connect. Needed for native USB port only

	configuration.initialize();

	if (configuration.isAvailable())
	{
		wiFiNetwork.connectAsClient(configuration.getSsid(), configuration.getPassword());
		mdns.initialize(configuration.getDeviceDomainName(), wiFiNetwork.getLocalIPAddress());
		webServer.initialize();
	}
	else
	{
		int numNetworks = WiFi.scanNetworks();

		Serial.print(numNetworks);
		Serial.println(" Wi-Fi networks found.");
		int scannedNetworksLength = min(numNetworks, Bas::WebServer::MAX_SCANNED_NETWORKS);

		Bas::NetworkInfo scannedNetworks[Bas::WebServer::MAX_SCANNED_NETWORKS];

		for (size_t i = 0; i < scannedNetworksLength; i++)
		{
			scannedNetworks[i] = Bas::NetworkInfo{ WiFi.SSID(i), WiFi.RSSI(i), WiFi.encryptionType(i) };
		}

		wiFiNetwork.connectAsAccessPoint("Klok");
		webServer.initialize(scannedNetworks, scannedNetworksLength);
		webServer.setPageToServe(Bas::WebServer::page::CONFIGURATION_PAGE);
	}
}

void loop()
{
	wiFiNetwork.update();

	if (wiFiNetwork.isClient())
	{
		mdns.update();
	}

	webServer.update();
}
