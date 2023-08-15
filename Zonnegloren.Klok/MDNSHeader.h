// MDNSHeader.h

#ifndef _MDNSHEADER_h
#define _MDNSHEADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Bas
{
	class MdnsHeader
	{
	public:
		enum OpCode { Query, IQuery, Status };
		enum ResponseCode { NoErrorCondition, FormatError, ServerFailure, NameError, NotImplemented, Refused };
		typedef struct
		{
			uint16_t transactionIdBytes;
			bool     isRecursionDesired : 1;
			bool     isTruncated : 1;
			bool     isAuthoritiveAnswer : 1;
			uint8_t  opCodeByte : 4;
			bool     isAnswer : 1;
			uint8_t  responseCodeByte : 4;
			bool     isCheckingDisabled : 1;
			bool     isAuthenticatedData : 1;
			uint8_t  zReserved : 1;
			bool     isRecursionAvailable : 1;
			uint16_t numQuestionsBytes : 16;
			uint16_t numAnswersBytes : 16;
			uint16_t numAuthorityResourceRecordsBytes : 16;
			uint16_t numAdditionalResourceRecordsBytes : 16;
		} __attribute__((__packed__)) rawMdnsHeader_t;

	private:
		uint16_t transactionId;
		OpCode opCode;
		bool isQuery;
		bool isAuthorativeAnswer;
		bool isTruncated;
		bool isRecursionDesired;
		bool isRecursionAvailable;
		bool isCheckingDisabled;
		bool isAuthenticatedData;
		ResponseCode responseCode;
		int numQuestions;
		int numAnswers;
		int numAuthorityResourceRecords;
		int numAdditionalResourceRecords;

	public:
		MdnsHeader(const unsigned char bytes[]);
	
		static const int NUM_BYTES_IN_HEADER = 12;

		rawMdnsHeader_t getRawMdnsHeader();
		//uint16_t getTransactionId();
		//OpCode getOpCode();
		void setOpcode(OpCode opCode);
		bool getIsQuery();
		void setIsQuery(bool isQuery);

		//bool getIsAuthorativeAnswer();
		void setIsAuthorativeAnswer(bool isAuthorativeAnswer);

		//bool getIsTruncated();
		//bool getIsRecursionDesired();
		//bool getIsRecursionAvailable();
		//ResponseCode getResponseCode();
		void setResponseCode(ResponseCode responseCode);
		//bool getIsCheckingDisabled();
		//bool getIsAuthenticatedData();

		int getNumQuestions();
		void setNumQuestions(int numQuestions);
		//int getNumAnswers();
		void setNumAnswers(int numAnswers);
		//int getNumAuthorityResourceRecords();
		void setNumAuthorityResourceRecords(int numAuthorityResourceRecords);
		//int getNumAdditionalResourceRecords();
		void setNumAdditionalResourceRecords(int numAdditionalResourceRecords);
	};
}

#endif

