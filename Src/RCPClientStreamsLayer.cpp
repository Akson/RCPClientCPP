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

	PushStreamName("StdOut");
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

void RCPClientStreamsLayer::SendMessageToStream(const char *substreamName, const char *commands, const void *messageData, unsigned int messgeLengthInBytes)
{
	//If substream name starts with @ symbol, it is threated as a full stream name
	if(substreamName && substreamName[0] == '@')
		return SendMessageToSpecifiedStream(substreamName+1, commands, messageData, messgeLengthInBytes);
	
	std::string streamName = m_ConstantPrefix;
    if(!m_ConstantPrefix.empty()) streamName += m_SubstreamsSeparator;
    for(auto substreamNameIt = m_SubstreamNamesStack.begin(); substreamNameIt != m_SubstreamNamesStack.end(); substreamNameIt++)
    {
        if(substreamNameIt != m_SubstreamNamesStack.begin())
            streamName += m_SubstreamsSeparator;
        streamName += *substreamNameIt;
    }

    if(substreamName && strlen(substreamName))
    {
        if(m_SubstreamNamesStack.size() > 0)
            streamName += m_SubstreamsSeparator;
        streamName.append(substreamName);
    }

    SendMessageWithAddedSystemInfo(streamName.c_str(), commands, messageData, messgeLengthInBytes);
}

void RCPClientStreamsLayer::SendMessageToSpecifiedStream(const char *absoluteStreamName, const char *commands, const void *messageData, unsigned int messgeLengthInBytes)
{
    std::string streamName = m_ConstantPrefix;
    if(!m_ConstantPrefix.empty()) streamName += m_SubstreamsSeparator;
	streamName += absoluteStreamName;
    SendMessageWithAddedSystemInfo(streamName.c_str(), commands, messageData, messgeLengthInBytes);
}

void RCPClientStreamsLayer::SetStreamPrefix( const char *prefix )
{
	m_ConstantPrefix = std::string(prefix);
}
