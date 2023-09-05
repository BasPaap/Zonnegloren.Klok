#include "Hand.h"
#include "HandMotor.h"
#include "L9110SStepperDriver.h"
#include "StepperDriver.h"
#include <Stepper.h>
#include "TimeSpan.h"
#include <SPI.h>
#include "NetworkInfo.h"
#include <WiFiNINA.h>
#include "WiFiNetwork.h"
#include "Mdns.h"
#include "WebServer.h"
#include "Configuration.h"
#include "Clock.h"
#include "L9110SStepperDriver.h"
#include "HandMotor.h"
#include "Hand.h"
#include <Bas.Button.h>

const int clearConfigurationButtonPin = 10;
const unsigned long debounceDelay = 50;

Bas::Configuration configuration;
Bas::WiFiNetwork wiFiNetwork;
Bas::Mdns mdns;
Bas::WebServer webServer;
Bas::Button clearConfigurationButton { clearConfigurationButtonPin, debounceDelay, Bas::Button::LogLevel::none };
Bas::Clock clock;
Bas::L9110SStepperDriver minuteStepperDriver{ 720, 2, 3, 4, 5 };
Bas::L9110SStepperDriver hourStepperDriver{ 720, 6, 7, 8, 9 };
Bas::Hand minuteHand{ &clock, Bas::HandMotor { &minuteStepperDriver }, Bas::Hand::HandType::minute };
Bas::Hand hourHand{ &clock, Bas::HandMotor { &hourStepperDriver }, Bas::Hand::HandType::hour };

#include <Stepper.h>

void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial);  // wait for serial port to connect. Needed for native USB port only

	clock.setConstantSpeed(60);
	clock.begin();

	minuteHand.begin();
	hourHand.begin();

	clearConfigurationButton.begin(onClearConfigurationButtonPressed);
	configuration.begin();
		
	if (configuration.isAvailable())
	{
		wiFiNetwork.connectAsClient(configuration.getSsid(), configuration.getPassword(), configuration.getKeyIndex(), configuration.getEncryptionType(), onConnectionFailure);
		mdns.begin(configuration.getDeviceDomainName(), wiFiNetwork.getLocalIPAddress());
		webServer.begin(onConfigurationDataReceived, onControlDataReceived, onResetRequested, onCalibrationDataReceived);
		webServer.setPageToServe(Bas::WebServer::page::firstCalibrationPage);	// Because the clock has just powered up, we have no idea what time the hands are on yet, so we need to calibrate first.
	}
	else
	{
		int numNetworks = WiFi.scanNetworks();

		Serial.print(numNetworks);
		Serial.println(" Wi-Fi networks found.");
		int scannedNetworksLength = min(numNetworks, Bas::WebServer::maxScannedNetworks);

		Bas::NetworkInfo scannedNetworks[Bas::WebServer::maxScannedNetworks];

		for (size_t i = 0; i < scannedNetworksLength; i++)
		{
			scannedNetworks[i] = Bas::NetworkInfo{ WiFi.SSID(i), WiFi.RSSI(i), WiFi.encryptionType(i) };
		}

		wiFiNetwork.connectAsAccessPoint("Klok");
		mdns.begin("klok.local", wiFiNetwork.getLocalIPAddress());
		webServer.begin(onConfigurationDataReceived, onControlDataReceived, onResetRequested, onCalibrationDataReceived, scannedNetworks, scannedNetworksLength);
		webServer.setPageToServe(Bas::WebServer::page::configurationPage);
	}
}

void loop()
{
	clearConfigurationButton.update();
	wiFiNetwork.update();
	mdns.update();
	webServer.update();
	clock.update();	
	minuteHand.update();	
	hourHand.update();
}

void onConfigurationDataReceived(const char* ssid, const char* password, uint8_t keyIndex, const Bas::NetworkInfo::encryptionType_t encryptionType, const char* domainName)
{
	configuration.setSsid(ssid);
	configuration.setPassword(password);
	configuration.setKeyIndex(keyIndex);
	configuration.setEncryptionType(encryptionType);
	configuration.setDeviceDomainName(domainName);
	configuration.save();
}

void onCalibrationDataReceived(uint8_t hours, uint8_t minutes)
{
	Serial.print("Calibration data received.");
	// clock.calibrate(hours, minutes);
}

void onControlDataReceived()
{

}



void onConnectionFailure()
{
	Serial.println("Could not connect to the network, possibly because of incorrect settings. Clearing settings and rebooting to configuration mode.");
	configuration.clear();
	onResetRequested();
}

void onClearConfigurationButtonPressed()
{
	configuration.clear();
	onResetRequested();
}

void onResetRequested()
{
	Serial.println("Resetting arduino.");
	delay(1000);
	asm volatile ("jmp 0x7800");
}