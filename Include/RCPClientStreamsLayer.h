#pragma once
#include "RCPClientSystemInfoLayer.h"
#include <vector>

class RCPClientStreamsLayer : public RCPClientSystemInfoLayer
{
public:
    RCPClientStreamsLayer();
    virtual ~RCPClientStreamsLayer();

	void SetStreamPrefix(const char *prefix);
    void PushStreamName(const char *substreamName);
    void PopStreamName();
    void SendMessageToStream(const char *value, const char *substreamName = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0);
	void SendMessageToSpecifiedStream(const char *value, const char *fullStreamName  = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0);

private:
    std::vector<std::string> m_SubstreamNamesStack;
    std::string m_SubstreamsSeparator;
	std::string m_ConstantPrefix;
};