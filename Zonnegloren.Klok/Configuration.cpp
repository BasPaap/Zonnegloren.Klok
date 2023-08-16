// 
// 
// 

#include "Configuration.h"
#include <EEPROM.h>

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
			value[i] = EEPROM.read(address + i) ^ ('B' + address + i);
		}

		value[valueLength] = 0;

		return true;
	}
}

void Bas::Configuration::initialize()
{
	int ssidAddress = 0;
	if (!readValue(ssidAddress, MAX_SSID_LENGTH, this->ssid))
	{
		return;
	}

	int passwordAddress = ssidAddress + strlen(this->ssid);
	if (!readValue(passwordAddress, MAX_PASSWORD_LENGTH, this->password))
	{
		return;
	}

	int domainNameAddress = passwordAddress + strlen(this->password);
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
}



bool Bas::Configuration::isAvailable()
{
	return this->areValuesFound;
}

void Bas::Configuration::save()
{
	// Encrypt the configuration values and write them to non-volatile memory.
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

void Bas::Configuration::setDeviceDomainNAme(const char* deviceDomainName)
{
	strcpy(this->deviceDomainName, deviceDomainName);
}
