#pragma once

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

	void ConnectToServer(const char* ServerAddress);

protected:
	void SendMessageToServer(const char *streamName, const char *stringMessage, const void *pBinaryMessageBuffer, size_t binaryMessgeLengthInBytes);

private:
	//ZMQ machinery
	void *m_Socket;
	void *m_Context;

private:
	//No copies
	RCPClientNetworkLayer(RCPClientNetworkLayer const&);
	void operator=(RCPClientNetworkLayer const&);
};