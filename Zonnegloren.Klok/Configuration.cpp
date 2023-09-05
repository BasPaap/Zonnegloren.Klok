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
	EEPROM.update(address, valueLength);
	
	for (size_t i = 0; i < valueLength; i++)
	{
		int characterAddress = address + i + 1;
		uint8_t hashedValue = hash(value[i], characterAddress);
		EEPROM.update(characterAddress, hashedValue);		
	}
}

uint8_t Bas::Configuration::hash(uint8_t value, int salt)
{
	return value ^ (hashValue + salt);
}

void Bas::Configuration::begin()
{
	int ssidAddress = 0;
	if (!readValue(ssidAddress, maxSsidLength, this->ssid))
	{
		return;
	}

	int passwordAddress = ssidAddress + strlen(this->ssid) + 1;
	if (!readValue(passwordAddress, maxPasswordLength, this->password))
	{
		return;
	}
	
	int domainNameAddress = passwordAddress + strlen(password) + 1;
	if (!readValue(domainNameAddress, maxDomainNameLength, this->deviceDomainName))
	{
		return;
	}
	
	int keyIndexAddress = domainNameAddress + strlen(deviceDomainName) + 1;
	this->keyIndex = EEPROM.read(keyIndexAddress);
	
	int encryptionTypeAddress = keyIndexAddress + maxKeyIndexLength;
	switch (EEPROM.read(encryptionTypeAddress))
	{
	case 1:
		this->encryptionType = Bas::NetworkInfo::wpa;
		break;
	case 2:
		this->encryptionType = Bas::NetworkInfo::wep;
		break;
	case 0:
	default:
		this->encryptionType = Bas::NetworkInfo::none;
		break;
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
		writeValue(domainNameAddress, this->deviceDomainName, strlen(this->deviceDomainName) - strlen(domainNameTld));
		
		int keyIndexAddress = domainNameAddress + strlen(this->deviceDomainName) - strlen(domainNameTld) + 1;
		EEPROM.put(keyIndexAddress, this->keyIndex);
		
		int encryptionTypeAddress = keyIndexAddress + maxKeyIndexLength;
		EEPROM.put(encryptionTypeAddress, this->encryptionType);		
	}	
}

void Bas::Configuration::clear()
{
	for (size_t i = 0; i < EEPROM.length(); i++)
	{
		EEPROM.put(i, 0);
	}
	
	Serial.println("Configuration cleared.");
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
		
	// Ensure that the domain name ends in .local
	if (strlen(deviceDomainName) < strlen(domainNameTld + 1)) // The domain name should be at least 7 characters: a.local		
	{
		strcat(this->deviceDomainName, domainNameTld);
	}
	else if (strcmp(domainNameTld, this->deviceDomainName + (strlen(this->deviceDomainName) - 6)) != 0)
	{		
		strcat(this->deviceDomainName, domainNameTld);
	}
}

uint8_t Bas::Configuration::getKeyIndex()
{
	return keyIndex;
}

void Bas::Configuration::setKeyIndex(uint8_t keyIndex)
{
	this->keyIndex = keyIndex;
}

Bas::NetworkInfo::encryptionType_t Bas::Configuration::getEncryptionType()
{
	return encryptionType;
}

void Bas::Configuration::setEncryptionType(Bas::NetworkInfo::encryptionType_t encryptionType)
{
	this->encryptionType = encryptionType;
}
