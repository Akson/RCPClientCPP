#pragma once
#include "RCPClientNetworkLayer.h"

class RCPCLIENT_API RCPClientSystemInfoLayer : public RCPClientNetworkLayer
{
public:
	RCPClientSystemInfoLayer();
	~RCPClientSystemInfoLayer();

	void SetThreadName(const char* threadName);

//protected:
	void PushToStreamWithAddedSystemInfo(const char* value, const char* streamName = 0, const char* commands = 0, const void* pBinaryData = 0, unsigned int binaryDataLength = 0);

private:
	//Thread alias name
	std::map<unsigned long, std::string> m_ThreadNames;

	//No copies
	RCPClientSystemInfoLayer(RCPClientSystemInfoLayer const&);
	void operator=(RCPClientSystemInfoLayer const&);
};