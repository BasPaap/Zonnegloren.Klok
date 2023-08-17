// 
// 
// 

#include "Configuration.h"
#include <EEPROM.h>
#include <avr/wdt.h>

bool Bas::Configuration::readValue(int address, int maxLength, char* value)
{
	int valueLength = EEPROM.read(address);
	
	if (valueLength == 0 || valueLength > maxLength)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < valueLength; i++)
		{
			int characterAddress = address + i + 1;
			value[i] = hash(EEPROM.read(characterAddress), characterAddress);			
		}

		value[valueLength] = 0;

		return true;
	}
}

void Bas::Configuration::writeValue(int address, char* value)
{
	writeValue(address, value, strlen(value));
}

void Bas::Configuration::writeValue(int address, char* value, size_t valueLength)
{	
	EEPROM.write(address, valueLength);
	
	for (size_t i = 0; i < valueLength; i++)
	{
		int characterAddress = address + i + 1;
		uint8_t hashedValue = hash(value[i], characterAddress);
		EEPROM.update(characterAddress, hashedValue);		
	}
}

uint8_t Bas::Configuration::hash(uint8_t value, int salt)
{
	return value ^ (HASH_VALUE + salt);
}

void Bas::Configuration::resetArduino() 
{
	asm ("jmp 0x7800");
}

void Bas::Configuration::initialize()
{
	int ssidAddress = 0;
	if (!readValue(ssidAddress, MAX_SSID_LENGTH, this->ssid))
	{
		return;
	}

	int passwordAddress = ssidAddress + strlen(this->ssid) + 1;
	if (!readValue(passwordAddress, MAX_PASSWORD_LENGTH, this->password))
	{
		return;
	}

	int domainNameAddress = passwordAddress + strlen(this->password) + 1;
	if (!readValue(domainNameAddress, MAX_DOMAIN_NAME_LENGTH, this->deviceDomainName))
	{
		return;
	}

	int domainNameLength = strlen(this->deviceDomainName);
	this->deviceDomainName[domainNameLength] = '.';
	this->deviceDomainName[domainNameLength + 1] = 'l';
	this->deviceDomainName[domainNameLength + 2] = 'o';
	this->deviceDomainName[domainNameLength + 3] = 'c';
	this->deviceDomainName[domainNameLength + 4] = 'a';
	this->deviceDomainName[domainNameLength + 5] = 'l';
	this->deviceDomainName[domainNameLength + 6] = 0;

	this->areValuesFound = true;

	Serial.println(this->ssid);
	Serial.println(this->password);
	Serial.println(this->deviceDomainName);
}

bool Bas::Configuration::isAvailable()
{
	return this->areValuesFound;
}

void Bas::Configuration::save()
{
	if (strlen(this->ssid) &&
		strlen(this->password) &&
		strlen(this->deviceDomainName))
	{
		// Encrypt the configuration values and write them to non-volatile memory.
		int ssidAddress = 0;
		writeValue(ssidAddress, this->ssid);
		
		int passwordAddress = ssidAddress + strlen(this->ssid) + 1;
		writeValue(passwordAddress, this->password);

		int domainNameAddress = passwordAddress + strlen(this->password) + 1;
		writeValue(domainNameAddress, this->deviceDomainName, strlen(this->deviceDomainName) - 6);
	}	
}

void Bas::Configuration::reset()
{
	for (size_t i = 0; i < EEPROM.length(); i++)
	{
		EEPROM.put(i, 0);
	}

	// Reset the arduino
	Serial.println("Configuration cleared, resetting arduino.");
	resetArduino();
}

char* Bas::Configuration::getSsid()
{
	return ssid;
}

void Bas::Configuration::setSsid(const char* ssid)
{	
	strcpy(this->ssid, ssid);
}

char* Bas::Configuration::getPassword()
{
	return password;
}

void Bas::Configuration::setPassword(const char* password)
{
	strcpy(this->password, password);
}

char* Bas::Configuration::getDeviceDomainName()
{
	return deviceDomainName;
}

void Bas::Configuration::setDeviceDomainName(const char* deviceDomainName)
{
	strcpy(this->deviceDomainName, deviceDomainName);
}
