#pragma once

namespace RCP
{

class RCPClientNetworkLayer
{
public:
    RCPClientNetworkLayer();
    virtual ~RCPClientNetworkLayer();

    //Connects to a give server and port. Use ZMQ format like "tcp://127.0.0.1:55557"
    int ConnectToServer(const char *ServerAddress);

    //Closes ZMQ socket and contexts (all other information is preserved)
    void Disconnect();

    bool IsConnected();

protected:
    void SendMessageToServer(const char *streamName, const char *info, const void *messageData, size_t messgeLengthInBytes);

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