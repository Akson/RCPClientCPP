#pragma once
#include <string>

class RCPClient
{
private:
	//No copies
	RCPClient(RCPClient const&);
	void operator=(RCPClient const&);

public:
	RCPClient();
	~RCPClient();

	//Connect to a remote server
	void ConnectToServer(const char* ServerAddress);

	//Send string to a server
	void RCPClient::Print(const char* Value, const char* StreamName = 0, const char* Filters = 0, const char* Destinations = 0);

private:
	//Internal implementation
	unsigned long GenerateLocalTimeStamp();
	void SendMessageToServer(const char* Value, const char* StreamName, const char* Filters, const char* Destinations, const void* pBinaryData, unsigned int binaryDataLength);

private:
	//Here we store the application start time for generating timestamps
	unsigned long m_StartTime;

	//ZMQ machinery
	void *m_Socket;
	void *m_Context;
};