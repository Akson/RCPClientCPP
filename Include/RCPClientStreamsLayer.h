#pragma once
#include "RCPClientSystemInfoLayer.h"
#include <vector>

namespace RCP
{

class RCPClientStreamsLayer : public RCPClientSystemInfoLayer
{
public:
    RCPClientStreamsLayer();
    virtual ~RCPClientStreamsLayer();

	void SetStreamPrefix(const char *prefix);
    void PushStreamName(const char *substreamName);
    void PopStreamName();
    void SendMessageToStream(const char *substreamName, const char *commands, const void *messageData, size_t messgeLengthInBytes);
	void SendMessageToSpecifiedStream(const char *absoluteStreamName, const char *commands, const void *messageData, size_t messgeLengthInBytes);
	void SetStreamNameForNextMessage(const char *substreamName);

private:
    ::std::vector<::std::string> m_SubstreamNamesStack;
    ::std::string m_SubstreamsSeparator;
	::std::string m_ConstantPrefix;
	::std::string m_StreamNameForNextMessage;
};

}