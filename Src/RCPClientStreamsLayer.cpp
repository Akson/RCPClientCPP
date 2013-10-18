#include "RCPClientStreamsLayer.h"
#include "zmq.h"
#include "RCPTools.h"
#include <sstream>

RCPClientStreamsLayer::RCPClientStreamsLayer(void)
    : m_SubstreamsSeparator("/")
{
	std::ostringstream stringStream;
	stringStream << "[";
	stringStream << GetApplicationName();
	stringStream << "]";
	m_ConstantPrefix = stringStream.str();

	PushStreamName("DefaultStream");
}

RCPClientStreamsLayer::~RCPClientStreamsLayer(void)
{
}

void RCPClientStreamsLayer::PushStreamName(const char *substreamName)
{
    m_SubstreamNamesStack.push_back(std::string(substreamName));
}

void RCPClientStreamsLayer::PopStreamName()
{
    m_SubstreamNamesStack.erase(m_SubstreamNamesStack.end() - 1);
}

void RCPClientStreamsLayer::SendMessageToStream(const char *value, const char *substreamName /*= 0*/, const char *commands /*= 0*/, const void *pBinaryData /*= 0*/, unsigned int binaryDataLength /*= 0*/)
{
	//If substream name starts with @ symbol, it is threated as a full stream name
	if(substreamName && substreamName[0] == '@')
		SendMessageToSpecifiedStream(value, substreamName+1, commands, pBinaryData, binaryDataLength);
	
	std::string streamName = m_ConstantPrefix;
    if(!m_ConstantPrefix.empty()) streamName += m_SubstreamsSeparator;
    for(auto substreamNameIt = m_SubstreamNamesStack.begin(); substreamNameIt != m_SubstreamNamesStack.end(); substreamNameIt++)
    {
        if(substreamNameIt != m_SubstreamNamesStack.begin())
            streamName += m_SubstreamsSeparator;
        streamName += *substreamNameIt;
    }

    if(substreamName)
    {
        if(m_SubstreamNamesStack.size() > 0)
            streamName += m_SubstreamsSeparator;
        streamName.append(substreamName);
    }

    SendMessageWithAddedSystemInfo(value, streamName.c_str(), commands, pBinaryData, binaryDataLength);
}

void RCPClientStreamsLayer::SendMessageToSpecifiedStream(const char *value, const char *fullStreamName /*= 0*/, const char *commands /*= 0*/, const void *pBinaryData /*= 0*/, unsigned int binaryDataLength /*= 0*/)
{
    std::string streamName = m_ConstantPrefix;
    if(!m_ConstantPrefix.empty()) streamName += m_SubstreamsSeparator;
	streamName += fullStreamName;
    SendMessageWithAddedSystemInfo(value, streamName.c_str(), commands, pBinaryData, binaryDataLength);
}

void RCPClientStreamsLayer::SetStreamPrefix( const char *prefix )
{
	m_ConstantPrefix = std::string(prefix);
}
