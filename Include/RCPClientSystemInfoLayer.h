#pragma once
#include "RCPClientNetworkLayer.h"
#include <string>

class RCPClientSystemInfoLayer : public RCPClientNetworkLayer
{
public:
    RCPClientSystemInfoLayer();
    ~RCPClientSystemInfoLayer();

    void SetThreadName(const char *threadName);

protected:
    void SendMessageWithAddedSystemInfo(const char *value, const char *streamName = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0);

private:
    std::string m_ThreadName;//Thread alias name
	std::string m_ApplicationName;
	std::string m_InstanceIdentifier;
};