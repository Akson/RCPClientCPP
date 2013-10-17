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

void RCPClient::Send(const char *value, const char *substreamName /*= 0*/, const char *commands /*= 0*/, const void *pBinaryData /*= 0*/, unsigned int binaryDataLength /*= 0*/)
{
	//If substream name starts with @ symbol, it is threated as a full stream name
	if(substreamName && substreamName[0] == '@')
	{
		m_pImplementation->SendMessageToSpecifiedStream(value, substreamName+1, commands, pBinaryData, binaryDataLength);
	}
	else
	{
		m_pImplementation->SendMessageToCurrentStream(value, substreamName, commands, pBinaryData, binaryDataLength);
	}
}

void RCPClient::Disconnect()
{
    m_pImplementation->Disconnect();
}

void RCPClient::SetStreamPrefix( const char *prefix )
{
	m_pImplementation->SetStreamPrefix(prefix);
}
