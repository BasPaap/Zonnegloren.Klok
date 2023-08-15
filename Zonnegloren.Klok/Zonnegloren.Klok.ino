
#include <WiFiNINA.h>
#include "WiFiNetwork.h"
#include "Mdns.h"
#include "WebServer.h"


Bas::WiFiNetwork wiFiNetwork;
Bas::Mdns mdns;
Bas::WebServer webServer;

void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial);  // wait for serial port to connect. Needed for native USB port only

	wiFiNetwork.connectAsClient("foo", "bar");
	mdns.initialize("klok.local", wiFiNetwork.getLocalIPAddress());
	webServer.initialize();
}

void loop()
{
	mdns.update();
	webServer.update();
}
