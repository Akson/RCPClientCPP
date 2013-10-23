#include "RCPClient.h"
#include "RCPClientStreamsLayer.h"
#include <stdarg.h>

using namespace RCP;

RCPClient::RCPClient(void)
    : m_pImplementation(0)
{
    m_pImplementation = new RCPClientStreamsLayer();
}

RCPClient::~RCPClient(void)
{
    delete(m_pImplementation);
}

void RCPClient::ConnectToServer(const char *ServerAddress)
{
    m_pImplementation->ConnectToServer(ServerAddress);
}

void RCPClient::SetThreadName(const char *threadName)
{
    m_pImplementation->SetThreadName(threadName);
}

void RCPClient::PushStreamName(const char *substreamName)
{
    m_pImplementation->PushStreamName(substreamName);
}

void RCPClient::PopStreamName()
{
    m_pImplementation->PopStreamName();
}

void RCPClient::Disconnect()
{
    m_pImplementation->Disconnect();
}

void RCPClient::SetStreamPrefix(const char *prefix)
{
    m_pImplementation->SetStreamPrefix(prefix);
}

void RCPClient::Send(const char *stringData, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
	m_pImplementation->SendMessageToStream(substreamName, commands, stringData, strlen(stringData));
}

void RCPClient::Send(char *stringData, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
	m_pImplementation->SendMessageToStream(substreamName, commands, stringData, strlen(stringData));
}

void RCPClient::SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
	m_pImplementation->SendMessageToStream(substreamName, commands, binaryData, binaryDataLengthInBytes);
}

void RCPClient::SendBinary(void *binaryData, unsigned int binaryDataLengthInBytes, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
	m_pImplementation->SendMessageToStream(substreamName, commands, binaryData, binaryDataLengthInBytes);
}

void RCPClient::Send(bool value, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
    Send(
        value ? "{\"Value\":true}" : "{\"Value\":false}",
        substreamName,
        commands ? (std::string("ParseJson();") + std::string(commands)).c_str() : "ParseJson()"
    );
}

void RCPClient::SendFormated( const char *fmt, ... )
{
	char buffer[4096];

	//Just copy output to a standard console for now.
	int res;
	va_list ap;
	va_start(ap, fmt);
	res = vsprintf_s(buffer, fmt, ap);
	va_end(ap);

	Send(buffer);
}

void RCPClient::SendFormated( const char *streamName, const char *fmt, ... )
{
	char buffer[4096];

	//Just copy output to a standard console for now.
	int res;
	va_list ap;
	va_start(ap, fmt);
	res = vsprintf_s(buffer, fmt, ap);
	va_end(ap);

	Send(buffer, streamName);
}

RCPClient* RCP::RCPClient::Set( const char *key, const char *value )
{
	m_pImplementation->SetExtraData(key, value);
	return this;
}


