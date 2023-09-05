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
	class Mdns
	{
		static const int maxDomainNameLength = 253;
		static const int maxDnsPacketSize = 512;
		static const int queryTypeA = 0x01;
		static const int queryTypeHttps = 0x41;

		const IPAddress mdnsAddress{ 224, 0, 0, 251 };
		unsigned const int mdnsPort = 5353;
		const int maxLabelLength = 63;
		const int ignoreFurtherQuestions = -1;
		char * deviceDomainName;
		IPAddress localIPAddress;
		WiFiUDP udp;

		void handleMdnsPacket(const unsigned char packetBuffer[], int packetBufferSize);
		int handleMdnsQuestion(const unsigned char packetBuffer[], int packetBufferSize, uint16_t questionFirstByteIndex);
		void getRequestedDomainName(const unsigned char packetBuffer[], uint16_t domainNameFirstByteIndex, char domainName[], uint8_t* pDomainNameFieldLength);
		void getDomainNameLabel(const unsigned char packetBuffer[], uint16_t labelFirstByteIndex, char domainNameLabel[], uint8_t* pDomainNameLabelFieldLength, uint16_t* pNextDomainNameLabelByteIndex, bool* pIsTerminatedByCompressionLabel);
		const char* getQueryTypeName(uint16_t queryType);
		void domainNameToDnsDomainName(const char* domainName, unsigned char* dnsDomainName, int* dnsDomainNameSize);
		void uint16ToByteArray(uint16_t value, uint8_t* byteArray);
		void uint32ToByteArray(uint32_t value, uint8_t* byteArray);

	public:
		void begin(char domainName[], IPAddress localIPAddress);
		void update();
	};
}

#endif

