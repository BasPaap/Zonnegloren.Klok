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

char* Bas::Configuration::getSsid()
{
	return ssid;
}

char* Bas::Configuration::getPassword()
{
	return password;
}

char* Bas::Configuration::getDeviceDomainName()
{
	return deviceDomainName;
}
