// MDNS.h

#ifndef _MDNS_h
#define _MDNS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<WiFiUdp.h>

namespace Bas
{
	const int MAX_DOMAIN_NAME_LENGTH = 253;
	const int MAX_DNS_PACKET_SIZE = 512;
	const int QUERY_TYPE_A = 0x01;
	const int QUERY_TYPE_HTTPS = 0x41;

	class Mdns
	{
		const IPAddress MDNS_ADDRESS{ 224, 0, 0, 251 };
		unsigned const int MDNS_PORT = 5353;
		const int MAX_LABEL_LENGTH = 63;
		const int IGNORE_FURTHER_QUESTIONS = -1;
		char * deviceDomainName;
		IPAddress localIPAddress;
		WiFiUDP udp;

		void handleMdnsPacket(const unsigned char packetBuffer[], int packetBufferSize);
		int handleMdnsQuestion(const unsigned char packetBuffer[], int packetBufferSize, uint16_t questionFirstByteIndex);
		void getRequestedDomainName(const unsigned char packetBuffer[], uint16_t domainNameFirstByteIndex, char domainName[], uint8_t* pDomainNameFieldLength);
		void getDomainNameLabel(const unsigned char packetBuffer[], uint16_t labelFirstByteIndex, char domainNameLabel[], uint8_t* pDomainNameLabelFieldLength, uint16_t* pNextDomainNameLabelByteIndex, bool* pIsTerminatedByCompressionLabel);
		bool isCompressionLabelCharacter(const char character);
		const char * getQueryTypeName(uint16_t queryType);
		void domainNameToDnsDomainName(const char* domainName, unsigned char* dnsDomainName, int* dnsDomainNameSize);
		void uint16ToByteArray(uint16_t value, uint8_t* byteArray);
		void uint32ToByteArray(uint32_t value, uint8_t* byteArray);

	public:
		Mdns();
		void initialize(char domainName[], IPAddress localIPAddress);
		void update();
	};
}

#endif

