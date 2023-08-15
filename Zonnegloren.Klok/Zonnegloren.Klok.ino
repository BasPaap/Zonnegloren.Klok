
#include <WiFiNINA.h>
#include "Mdns.h"
#include "WiFiNetwork.h"

Bas::WiFiNetwork wiFiNetwork;
Bas::Mdns mdns;

void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial);  // wait for serial port to connect. Needed for native USB port only

	wiFiNetwork.connectAsClient("foo", "bar");
	mdns.initialize("klok.local", wiFiNetwork.getLocalIPAddress());
}

void loop()
{
	mdns.update();
}
