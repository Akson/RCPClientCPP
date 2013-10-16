#pragma once
#include "RCPClientNetworkLayer.h"
#include <string>

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
	std::string m_ThreadName;

	//No copies
	RCPClientSystemInfoLayer(RCPClientSystemInfoLayer const&);
	void operator=(RCPClientSystemInfoLayer const&);
};