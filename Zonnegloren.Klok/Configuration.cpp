// 
// 
// 

#include "Configuration.h"

void Bas::Configuration::initialize()
{
}

bool Bas::Configuration::isAvailable()
{
	return false;
}

void Bas::Configuration::save()
{
	// Encrypt the configuration values and write them to non-volatile memory.
}

char* Bas::Configuration::getSsid()
{
	return ssid;
}

void Bas::Configuration::setSsid(char* ssid)
{
	this->ssid = ssid;
}

char* Bas::Configuration::getPassword()
{
	return password;
}

void Bas::Configuration::setPassword(char* password)
{
	this->password = password;
}

char* Bas::Configuration::getDeviceDomainName()
{
	return deviceDomainName;
}

void Bas::Configuration::setDeviceDomainNAme(char* deviceDomainName)
{
	this->deviceDomainName = deviceDomainName;
}
