#pragma once

class RCPClientNetworkLayer
{
public:
	RCPClientNetworkLayer();
	virtual ~RCPClientNetworkLayer();

	int ConnectToServer(const char* ServerAddress);
	void Disconnect();

protected:
	void SendMessageToServer(const char *streamName, const char *stringMessage, const void *pBinaryMessageBuffer, size_t binaryMessgeLengthInBytes);

private:
	//ZMQ machinery
	void *m_Socket;
	void *m_Context;
	bool m_Connected;

private:
	//No copies
	RCPClientNetworkLayer(RCPClientNetworkLayer const&);
	void operator=(RCPClientNetworkLayer const&);
};