
#include <WiFiNINA.h>
#include "WiFiNetwork.h"
#include "Mdns.h"
#include "WebServer.h"
#include "Configuration.h"
#include "Config-HTML.h"

Bas::Configuration configuration;
Bas::WiFiNetwork wiFiNetwork;
Bas::Mdns mdns;
Bas::WebServer webServer { configuration };

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
		wiFiNetwork.connectAsAccessPoint("Klok");
		webServer.initialize();		
		webServer.setPageToServe(config_html);
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
