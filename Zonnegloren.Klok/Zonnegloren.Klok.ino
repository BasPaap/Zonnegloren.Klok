
#include "MDNSHeader.h"
#include <WiFiNINA.h>
#include "Mdns.h"

Bas::Mdns mdns;

void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial);  // wait for serial port to connect. Needed for native USB port only

	mdns.initialize("klok.local", IPAddress{127, 0, 0, 1});
}

void loop()
{
	mdns.update();
}
