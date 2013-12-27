#include "RCPClient.h"
#include "RCPClientNetworkLayer.h"
#include <stdarg.h>
#include "json/json.h"
#include <chrono>


using namespace RCP;



RCPClient::RCPClient(void)
{
}

RCPClient::~RCPClient(void)
{
}

RCPClient& RCPClient::Stream(const std::string &stream)
{
	SetValueForNextMessage("Stream", stream);
    return *this;
}

RCPClient& RCP::RCPClient::Set(const char *key, const std::string &value, bool permanent)
{
	SetValueForNextMessage(key, value, permanent);
	return *this;
}

RCPClient& RCP::RCPClient::Set(const char *key, int value, bool permanent)
{
	SetValueForNextMessage(key, std::to_string(value), permanent);
	return *this;
}

RCPClient& RCP::RCPClient::Set(const char *key, float value, bool permanent)
{
	SetValueForNextMessage(key, std::to_string(value), permanent);
	return *this;
}

void RCPClient::Send(const char *stringData)
{
    SendMessageToStream(0, stringData, strlen(stringData));
}

void RCPClient::SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes)
{
	Set("DataType", "Binary");
    SendMessageToStream(0, binaryData, binaryDataLengthInBytes);
}

void RCPClient::Send(bool value)
{
	Set("DataType", "JSON");
    Send(value ? "{\"_Value\":true}" : "{\"_Value\":false}");
}

void RCPClient::SendFormated(const char *fmt, ...)
{
    char buffer[4096];

    //Just copy output to a standard console for now.
    int res;
    va_list ap;
    va_start(ap, fmt);
    res = vsprintf_s(buffer, fmt, ap);
    va_end(ap);

	SendMessageToStream(0, buffer, strlen(buffer));
}

