#include "RCPClientNetworkLayer.h"
#include "zmq.h"
#include <winbase.h>
#include <stdio.h>

RCPClientNetworkLayer::RCPClientNetworkLayer(void)
    : m_Context(0)
    , m_Socket(0)
    , m_Connected(false)
{
}

RCPClientNetworkLayer::~RCPClientNetworkLayer(void)
{
    Disconnect();
}

void RCPClientNetworkLayer::SendMessageToServer(const char *streamName, const char *messageInfo, const void *messageData, size_t dataLengthInBytes)
{
    //Send message only if we are connected
    if(m_Socket == 0) return;

    //Create ZMQ message
    //Message format: <stream name>0<message>0<binary data>
    size_t streamNameLength = strlen(streamName);
    size_t infoLength = strlen(messageInfo);
    size_t messageLength = streamNameLength + 1 + infoLength + 1 + dataLengthInBytes;
    zmq_msg_t zmqMsg;
    zmq_msg_init_size(&zmqMsg, messageLength);
    char *pZmqMessage = reinterpret_cast<char *>(zmq_msg_data(&zmqMsg));


    //Copy stream name
    memcpy(pZmqMessage, streamName, streamNameLength);
    pZmqMessage += streamNameLength;

    //Add 0 divider
    *pZmqMessage = 0;
    pZmqMessage += 1;

    //Copy string message data
    memcpy(pZmqMessage, messageInfo, infoLength);
    pZmqMessage += infoLength;

    //Add 0 divider
    *pZmqMessage = 0;
    pZmqMessage += 1;

    //Copy binary data
    memcpy(pZmqMessage, messageData, dataLengthInBytes);


    //Send ZMQ message to the server
    int res = zmq_msg_send(&zmqMsg, m_Socket, 0);
}

int RCPClientNetworkLayer::ConnectToServer(const char *ServerAddress)
{
    Disconnect();

    m_Context = zmq_init(1);
    if(m_Context == NULL)
        return zmq_errno();

    m_Socket = zmq_socket(m_Context, ZMQ_PUB);
    if(m_Socket == NULL)
        return zmq_errno();

    if(zmq_connect(m_Socket, ServerAddress))
        return zmq_errno();

    m_Connected = true;

    return 0;
}

void RCPClientNetworkLayer::Disconnect()
{
    if(m_Connected)
    {
        zmq_close(m_Socket);
        m_Socket = 0;
        zmq_ctx_destroy(m_Context);
        m_Context = 0;
        m_Connected = false;
    }
}
