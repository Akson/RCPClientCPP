#pragma once

namespace RCP
{

class RCPClientNetworkLayer
{
public:
    RCPClientNetworkLayer();
    virtual ~RCPClientNetworkLayer();

    int ConnectToServer(const char *ServerAddress);
    void Disconnect();

    void SendMessageToServer(const char *streamName, const char *info, const void *messageData, size_t messgeLengthInBytes);
	bool IsConnected(){ return m_Socket!=0; }

private:
    //ZMQ machinery
    void *m_Socket;
    void *m_Context;
    bool m_Connected;

private:
    //No copies
    RCPClientNetworkLayer(RCPClientNetworkLayer const &);
    void operator=(RCPClientNetworkLayer const &);
};

}