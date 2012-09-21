#pragma once
#include <string>

class RCPClient
{
	//Print values
public:
	//Connect to a remote server
	void ConnectToServer(const char* ServerAddress);

	//Send string to a server
	void RCPClient::Print(const char* Value, const char* StreamName = 0, const char* Filters = 0, const char* Destinations = 0);

	//Singleton implementation
public:
	static RCPClient& getInstance()
	{
		static RCPClient instance; 
		return instance;
	}

private:
	RCPClient();
	~RCPClient();
	RCPClient(RCPClient const&);
	void operator=(RCPClient const&);

	//Internal implementation
private:
	unsigned long GenerateLocalTimeStamp();
	void SendMessageToServer(const char* Value, const char* StreamName, const char* Filters, const char* Destinations, const void* pBinaryData, unsigned int binaryDataLength);

private:
	//Here we store the application start time for generating timestamps
	unsigned long m_StartTime;

	//ZMQ machinery
	void *m_Socket;
	void *m_Context;
};

#define RCP RCPClient::getInstance()