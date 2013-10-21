#include "RCPClient.h"
#include "RCPClientStreamsLayer.h"

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

void RCPClient::SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
    m_pImplementation->SendMessageToStream(substreamName, commands, binaryData, binaryDataLengthInBytes);
}

void RCPClient::Send(bool value, const char *substreamName /*= 0*/, const char *commands /*= 0*/)
{
    Send(
        value ? "{\"Data\":true}" : "{\"Data\":false}",
        substreamName,
        commands ? (std::string("ParseJson();") + std::string(commands)).c_str() : "ParseJson()"
    );
}