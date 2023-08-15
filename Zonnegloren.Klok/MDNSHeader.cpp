// 
// 
// 

#include "MDNSHeader.h"

Bas::MdnsHeader::MdnsHeader(const unsigned char bytes[])
{
    rawMdnsHeader_t* rawHeader = (rawMdnsHeader_t*)bytes;

    transactionId = rawHeader->transactionIdBytes;
    opCode = (OpCode)rawHeader->opCodeByte;
    isQuery = !rawHeader->isAnswer;
    isAuthorativeAnswer = rawHeader->isAuthoritiveAnswer;
    isTruncated = rawHeader->isTruncated;
    isRecursionDesired = rawHeader->isRecursionDesired;
    isRecursionAvailable = rawHeader->isRecursionAvailable;
    isCheckingDisabled = rawHeader->isCheckingDisabled;
    isAuthenticatedData = rawHeader->isAuthenticatedData;
    responseCode = (ResponseCode)rawHeader->responseCodeByte;
    numQuestions = (rawHeader->numQuestionsBytes >> 8) | (rawHeader->numQuestionsBytes << 8); // The bytes are big endian whereas the arduino is little endian.
    numAnswers = (rawHeader->numAnswersBytes >> 8) | (rawHeader->numAnswersBytes << 8); // The bytes are big endian whereas the arduino is little endian.
    numAuthorityResourceRecords = (rawHeader->numAuthorityResourceRecordsBytes >> 8) | (rawHeader->numAuthorityResourceRecordsBytes << 8); // The bytes are big endian whereas the arduino is little endian.
    numAdditionalResourceRecords = (rawHeader->numAdditionalResourceRecordsBytes >> 8) | (rawHeader->numAdditionalResourceRecordsBytes << 8); // The bytes are big endian whereas the arduino is little endian.
}

bool Bas::MdnsHeader::getIsQuery()
{
    return isQuery;
}

void Bas::MdnsHeader::setIsQuery(bool isQuery)
{
    this->isQuery = isQuery;
}

int Bas::MdnsHeader::getNumQuestions()
{
    return numQuestions;
}

void Bas::MdnsHeader::setOpcode(OpCode opCode)
{
    this->opCode = opCode;
}

void Bas::MdnsHeader::setIsAuthorativeAnswer(bool isAuthorativeAnswer)
{
    this->isAuthorativeAnswer = isAuthorativeAnswer;
}

void Bas::MdnsHeader::setResponseCode(ResponseCode responseCode)
{
    this->responseCode = responseCode;
}

void Bas::MdnsHeader::setNumQuestions(int numQuestions)
{
    this->numQuestions = numQuestions;
}

void Bas::MdnsHeader::setNumAnswers(int numAnswers)
{
    this->numAnswers = numAnswers;
}

void Bas::MdnsHeader::setNumAuthorityResourceRecords(int numAuthorityResourceRecords)
{
    this->numAuthorityResourceRecords = numAuthorityResourceRecords;
}

void Bas::MdnsHeader::setNumAdditionalResourceRecords(int numAdditionalResourceRecords)
{
    this->numAdditionalResourceRecords = numAdditionalResourceRecords;
}

Bas::MdnsHeader::rawMdnsHeader_t Bas::MdnsHeader::getRawMdnsHeader()
{
    rawMdnsHeader_t rawHeader;
    rawHeader.transactionIdBytes = transactionId;
    rawHeader.isRecursionDesired = isRecursionDesired;
    rawHeader.isTruncated = isTruncated;
    rawHeader.isAuthoritiveAnswer = isAuthorativeAnswer;
    rawHeader.opCodeByte = opCode;
    rawHeader.isAnswer = !isQuery;
    rawHeader.responseCodeByte = responseCode;
    rawHeader.isCheckingDisabled = isCheckingDisabled;
    rawHeader.isAuthenticatedData = isAuthenticatedData;
    rawHeader.zReserved = 0;
    rawHeader.isRecursionAvailable = isRecursionAvailable;
    rawHeader.numQuestionsBytes = (numQuestions >> 8) | (numQuestions << 8);
    rawHeader.numAnswersBytes = (numAnswers >> 8) | (numAnswers << 8);
    rawHeader.numAuthorityResourceRecordsBytes = (numAuthorityResourceRecords >> 8) | (numAuthorityResourceRecords << 8);
    rawHeader.numAdditionalResourceRecordsBytes = (numAdditionalResourceRecords >> 8) | (numAdditionalResourceRecords << 8);

    return rawHeader;
}