#pragma once
#include "RCPClientNetworkLayer.h"

class RCPCLIENT_API RCPClient : public RCPClientNetworkLayer
{
private:
	//No copies
	RCPClient(RCPClient const&);
	void operator=(RCPClient const&);

public:
	RCPClient();
	~RCPClient();

	//Send string to a server
	void Print(const char* Value, const char* StreamName, const char* Commands = 0, const void* pBinaryData = 0, unsigned int binaryDataLength = 0);

	//Here we store the application start time for generating timestamps
	unsigned long GenerateLocalTimeStamp();
	unsigned long m_StartTime;
};