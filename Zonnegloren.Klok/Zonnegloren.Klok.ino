

void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);

	while (!Serial);  // wait for serial port to connect. Needed for native USB port only

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{


}
