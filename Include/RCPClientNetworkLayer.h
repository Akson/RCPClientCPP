#pragma once
#include <map>

#ifdef RCPCLIENT_EXPORTS
#define RCPCLIENT_API __declspec(dllexport)
#else
#define RCPCLIENT_API __declspec(dllimport)
#endif

class RCPCLIENT_API RCPClientNetworkLayer
{
public:
	RCPClientNetworkLayer();
	virtual ~RCPClientNetworkLayer();

	void SetServerAddress(const char* ServerAddress);

protected:
	void SendMessageToServer(const char *streamName, const char *stringMessage, const void *pBinaryMessageBuffer, size_t binaryMessgeLengthInBytes, unsigned long threadId);

private:
	//ZMQ machinery
	void CloseAllSockets();
	void *GetSocketForThreadId(unsigned long threadId);
	std::map<unsigned long, void*> m_Sockets;
	void *m_Context;
	std::string m_ServerAddress;

	//No copies
	RCPClientNetworkLayer(RCPClientNetworkLayer const&);
	void operator=(RCPClientNetworkLayer const&);
};