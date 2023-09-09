#include "MDNS.h"
#include "MdnsHeader.h"

void Bas::Mdns::begin(char domainName[], IPAddress localIPAddress)
{
	deviceDomainName = domainName;
	this->localIPAddress = localIPAddress;

	if (logLevel != none)
	{
		Serial.print("Starting as ");
		Serial.print(deviceDomainName);
		Serial.print(" on ");
		Serial.println(this->localIPAddress);
	}

	udp.beginMulticast(mdnsAddress, mdnsPort);
}

void Bas::Mdns::update()
{
	// if there's data available, read a packet
	int packetBufferSize = udp.parsePacket();

	if (packetBufferSize && packetBufferSize <= maxDnsPacketSize)
	{
		// read the packet into packetBufffer
		unsigned char packetBuffer[maxDnsPacketSize];
		int totalBytesRead = 0;

		do
		{
			int numBytesRead = udp.read(packetBuffer + totalBytesRead, maxDnsPacketSize);
			totalBytesRead += numBytesRead;
		} while (totalBytesRead < packetBufferSize);

		if (logLevel == verbose)
		{
			Serial.print("Packet received, read ");
			Serial.print(totalBytesRead);
			Serial.print(" out of ");
			Serial.print(packetBufferSize);
			Serial.println(" bytes.");
		}
	
		handleMdnsPacket(packetBuffer, packetBufferSize);
	}
}

Bas::Mdns::Mdns(LogLevel logLevel = none) : logLevel(logLevel)
{	
}

void Bas::Mdns::handleMdnsPacket(const unsigned char packetBuffer[], int packetBufferSize)
{
	Bas::MdnsHeader mdnsHeader{ packetBuffer };

	if (mdnsHeader.getIsQuery() && mdnsHeader.getNumQuestions() > 0)
	{
		int questionByteIndex = Bas::MdnsHeader::numBytesInHeader;

		for (size_t i = 0; i < mdnsHeader.getNumQuestions(); i++)
		{
			if (packetBuffer[questionByteIndex] > maxLabelLength && packetBuffer[questionByteIndex] >> 6 != 0b11) // If the label is larger than the possible length and this is not a compression label, ignore the rest because something is messed up.
			{
				if (logLevel == verbose)
				{
					Serial.println("Incorrect label length, ignoring the rest of the message.");
				}

				break;
			}

			questionByteIndex = handleMdnsQuestion(packetBuffer, packetBufferSize, questionByteIndex);

			if (questionByteIndex == ignoreFurtherQuestions)
			{
				break;
			}
		}
	}
}

/// <summary>
/// Analyze the mDNS buffer and reply if there is a query for our domain name.
/// </summary>
/// <param name="packetBuffer">The mDNS message bytes.</param>
/// <param name="packetBufferSize">Size of the packet buffer.</param>
/// <param name="questionFirstByteIndex">Index of the first of the question's bytes in the packetbuffer.</param>
/// <returns></returns>
int Bas::Mdns::handleMdnsQuestion(const unsigned char packetBuffer[], int packetBufferSize, uint16_t questionFirstByteIndex)
{
	if (questionFirstByteIndex >= packetBufferSize)
	{
		if (logLevel == verbose)
		{
			Serial.print("Question byte index is larger than packet buffer size: index ");
			Serial.print(questionFirstByteIndex);
			Serial.print(", packet buffer size: ");
			Serial.println(packetBufferSize);
		}

		return ignoreFurtherQuestions;
	}
		
	char domainName[maxDomainNameLength + 1];
	uint8_t domainNameFieldLength = 0;

	getRequestedDomainName(packetBuffer, questionFirstByteIndex, domainName, &domainNameFieldLength);
	uint16_t queryType = packetBuffer[questionFirstByteIndex + domainNameFieldLength] << 8 | packetBuffer[questionFirstByteIndex + domainNameFieldLength + 1];

	if (logLevel == verbose)
	{
		Serial.print("\tMDNS: ");
		const char* queryTypeName = getQueryTypeName(queryType);
		Serial.print(queryTypeName);
		Serial.print(" type query received for ");
		Serial.println(domainName);
	}

	if (strcasecmp(deviceDomainName, domainName) == 0) // if this is a query for our domain name
	{
		if (queryType == queryTypeA || queryType == queryTypeHttps)
		{
			uint16_t queryClass = packetBuffer[questionFirstByteIndex + domainNameFieldLength + 2] << 8 | packetBuffer[questionFirstByteIndex + domainNameFieldLength + 3];
			bool isUnicast = (queryClass >> 15) & 0x01;

			uint16_t mdnsQueryClass = queryClass & 0x7FFF;

			Bas::MdnsHeader mdnsResponseHeader{ packetBuffer };
			mdnsResponseHeader.setIsQuery(false);
			mdnsResponseHeader.setOpcode(Bas::MdnsHeader::OpCode::Query);
			mdnsResponseHeader.setIsAuthorativeAnswer(true);
			mdnsResponseHeader.setResponseCode(Bas::MdnsHeader::ResponseCode::NoErrorCondition);
			mdnsResponseHeader.setNumQuestions(0);
			mdnsResponseHeader.setNumAnswers(1);
			mdnsResponseHeader.setNumAuthorityResourceRecords(0);
			mdnsResponseHeader.setNumAdditionalResourceRecords(0);
			Bas::MdnsHeader::rawMdnsHeader_t rawResponseHeader = mdnsResponseHeader.getRawMdnsHeader();

			const int queryTypeSize = 2;
			const int queryClassSize = 2;
			const int ttlSize = 4;
			const int rdLengthSize = 2;

			const uint32_t ttl = 60;
			const uint16_t rdLength = 4;
			uint8_t rData[rdLength];
			
			unsigned char dnsDomainName[maxDomainNameLength];
			int dnsDomainNameSize;
			domainNameToDnsDomainName(deviceDomainName, dnsDomainName, &dnsDomainNameSize);

			uint8_t queryTypeBytes[queryTypeSize];
			uint16ToByteArray(queryType, queryTypeBytes);

			uint8_t queryClassBytes[queryClassSize];
			uint16ToByteArray(queryClass, queryClassBytes);

			uint8_t ttlBytes[ttlSize];
			uint32ToByteArray(ttl, ttlBytes);

			uint8_t rdLengthBytes[rdLengthSize];
			uint16ToByteArray(rdLength, rdLengthBytes);

			for (size_t i = 0; i < rdLength; i++)
			{
				rData[i] = localIPAddress[i];
			}

			int replySize = Bas::MdnsHeader::numBytesInHeader + dnsDomainNameSize + queryTypeSize + queryClassSize + ttlSize + +rdLengthSize + rdLength;

			uint8_t replyBuffer[maxDnsPacketSize];

			memcpy(replyBuffer, &rawResponseHeader, Bas::MdnsHeader::numBytesInHeader);
			memcpy(replyBuffer + Bas::MdnsHeader::numBytesInHeader, dnsDomainName, dnsDomainNameSize);
			memcpy(replyBuffer + Bas::MdnsHeader::numBytesInHeader + dnsDomainNameSize, queryTypeBytes, queryTypeSize);
			memcpy(replyBuffer + Bas::MdnsHeader::numBytesInHeader + dnsDomainNameSize + queryTypeSize, queryClassBytes, queryClassSize);
			memcpy(replyBuffer + Bas::MdnsHeader::numBytesInHeader + dnsDomainNameSize + queryTypeSize + queryClassSize, ttlBytes, ttlSize);
			memcpy(replyBuffer + Bas::MdnsHeader::numBytesInHeader + dnsDomainNameSize + queryTypeSize + queryClassSize + ttlSize, rdLengthBytes, rdLengthSize);
			memcpy(replyBuffer + Bas::MdnsHeader::numBytesInHeader + dnsDomainNameSize + queryTypeSize + queryClassSize + ttlSize + rdLengthSize, rData, rdLength);

			IPAddress destinationAddress = isUnicast ? udp.remoteIP() : mdnsAddress;
			uint16_t destinationPort = isUnicast ? udp.remotePort() : mdnsPort;

			Serial.print("\tSending response to ");
			Serial.println(destinationAddress);

			udp.beginPacket(destinationAddress, destinationPort);
			udp.write(replyBuffer, replySize);
			int endSuccess = udp.endPacket();
		}
	}

	return questionFirstByteIndex + domainNameFieldLength + 4;
}

void Bas::Mdns::getRequestedDomainName(const unsigned char packetBuffer[], uint16_t domainNameFirstByteIndex, char domainName[], uint8_t* pDomainNameFieldLength)
{
	uint8_t domainNameLabelFieldLength = 0;
	uint16_t currentDomainNameLabelByteIndex = domainNameFirstByteIndex;
	uint16_t nextDomainNameLabelByteIndex = 0;
	const int MAX_DOMAIN_NAME_LABEL_LENGTH = 63;
	char domainNameLabel[MAX_DOMAIN_NAME_LABEL_LENGTH + 1];
	bool isTerminatedByCompressionLabel = false;

	domainName[0] = 0;
		
	do
	{
		domainNameLabel[0] = 0;
		getDomainNameLabel(packetBuffer, currentDomainNameLabelByteIndex, domainNameLabel, &domainNameLabelFieldLength, &nextDomainNameLabelByteIndex, &isTerminatedByCompressionLabel);
		
		// Append the label to the domain name we have so far, with a period as a separator.
		strcat(domainName, domainNameLabel);
		strcat(domainName, ".");

		if (!isTerminatedByCompressionLabel)
		{
			*pDomainNameFieldLength += domainNameLabelFieldLength;
		}

		currentDomainNameLabelByteIndex = nextDomainNameLabelByteIndex;
	} while (packetBuffer[currentDomainNameLabelByteIndex] != 0); // If the next byte read is 0, that terminates the domain name.


	// Remove the root period from the domain name.
	domainName[strlen(domainName) - 1] = 0;

	// If the domain was terminated by a compression label, don't forget to add the label's two bytes to the total length.
	if (isTerminatedByCompressionLabel)
	{
		*pDomainNameFieldLength += 2;
	}
	else // If it was not terminated by a compression label, it was terminated by a zero so count that one instead.
	{
		*pDomainNameFieldLength += 1;
	}
}

void Bas::Mdns::getDomainNameLabel(const unsigned char packetBuffer[], uint16_t labelFirstByteIndex, char domainNameLabel[], uint8_t* pDomainNameLabelFieldLength, uint16_t* pNextDomainNameLabelByteIndex, bool* pIsTerminatedByCompressionLabel)
{
	uint16_t currentLabelByteIndex = labelFirstByteIndex;
	
	if (packetBuffer[currentLabelByteIndex] >> 6 == 0b11) // If the first two bits are set, then this is a compression label.
	{
		// No label bytes or terminator byte will follow after the compression label, so we can tell our calling member that this ends the bytes used for the label in this message.
		*pIsTerminatedByCompressionLabel = true;

		// The next two bytes, with the two most significant bits removed are the index for the rest of the label.
		currentLabelByteIndex = (uint16_t)(packetBuffer[currentLabelByteIndex] ^ (packetBuffer[currentLabelByteIndex] >> 6) << 6) | (uint16_t)(packetBuffer[currentLabelByteIndex + 1]);
	}

	uint8_t labelLength = packetBuffer[currentLabelByteIndex];
	
	for (size_t i = 0; i < labelLength; i++)
	{
		domainNameLabel[i] = packetBuffer[currentLabelByteIndex + 1 + i];
	}
	domainNameLabel[labelLength] = 0;

	// If we are not currently reading the label pointed to by a compression label, return the length of the current label field (which is the length of the label plus the first byte indicating the length)
	*pDomainNameLabelFieldLength = labelLength + 1;

	*pNextDomainNameLabelByteIndex = currentLabelByteIndex + *pDomainNameLabelFieldLength;
}

const char* Bas::Mdns::getQueryTypeName(uint16_t queryType)
{
	switch (queryType)
	{
	case queryTypeA:
		return "A";

	case queryTypeHttps:
		return "HTTPS";

	default:
		char queryTypeName[10];
		itoa(queryType, queryTypeName, 10);
		return strcat(queryTypeName, " (other)");
	}
}

void Bas::Mdns::domainNameToDnsDomainName(const char* domainName, unsigned char* dnsDomainName, int* dnsDomainNameSize)
{
	int position = 1;
	int lastDot = 0;

	// Iterate through each character in the domain
	for (int i = 0; domainName[i] != '\0'; ++i) {
		if (domainName[i] == '.')
		{
			// Write the length of the label to the previous label's position
			dnsDomainName[lastDot] = i - lastDot;
			lastDot = position++;
		}
		else
		{
			// Write the character into the DNS message
			dnsDomainName[position++] = domainName[i];
		}
	}

	// Write the last label's length
	dnsDomainName[lastDot] = strlen(domainName) - lastDot;

	// Terminate with zero-length label to indicate end of domain
	dnsDomainName[position++] = 0;
	*dnsDomainNameSize = position;
}

void Bas::Mdns::uint16ToByteArray(uint16_t value, uint8_t* byteArray) 
{
	byteArray[0] = (value >> 8) & 0xFF; // Upper byte (most significant byte)
	byteArray[1] = value & 0xFF;
}

void Bas::Mdns::uint32ToByteArray(uint32_t value, uint8_t* byteArray) 
{
	byteArray[0] = (value >> 24) & 0xFF; // Highest byte
	byteArray[1] = (value >> 16) & 0xFF;
	byteArray[2] = (value >> 8) & 0xFF;
	byteArray[3] = value & 0xFF;         // Lowest byte
}
