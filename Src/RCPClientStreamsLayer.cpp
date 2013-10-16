#include "RCPClientStreamsLayer.h"
#include "zmq.h"

RCPClientStreamsLayer::RCPClientStreamsLayer(void)
    : m_SubstreamsSeparator("/")
{
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

void RCPClientStreamsLayer::SendMessageToCurrentStream(const char *value, const char *substreamName /*= 0*/, const char *commands /*= 0*/, const void *pBinaryData /*= 0*/, unsigned int binaryDataLength /*= 0*/)
{
    std::string streamName;
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
