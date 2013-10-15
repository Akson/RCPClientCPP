#include "RCPClientNetworkLayer.h"
#include "zmq.h"

RCPClientNetworkLayer::RCPClientNetworkLayer(void)
    : m_Context(0)
    , m_Socket(0)
{
}

RCPClientNetworkLayer::~RCPClientNetworkLayer(void)
{
}

void RCPClientNetworkLayer::SendMessageToServer(const char *streamName, const char *stringMessage, const void *pBinaryMessageBuffer, size_t binaryMessgeLengthInBytes)
{
    //Send message only if we are connected
    if(m_Socket == 0) return;

	//Create ZMQ message
    //Message format: <stream name>0<message>
	size_t streamNameLength = strlen(streamName);
	size_t stringMessageLength = strlen(stringMessage);
    size_t messageLength = streamNameLength + 1 + stringMessageLength + 1 + binaryMessgeLengthInBytes;
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
	memcpy(pZmqMessage, stringMessage, stringMessageLength);
	pZmqMessage += stringMessageLength;

	//Add 0 divider
	*pZmqMessage = 0;
	pZmqMessage += 1;

	//Copy binary data
	memcpy(pZmqMessage, pBinaryMessageBuffer, binaryMessgeLengthInBytes);


    //Send ZMQ message to the server
    int res = zmq_msg_send(&zmqMsg, m_Socket, 0);
}

void RCPClientNetworkLayer::ConnectToServer(const char *ServerAddress)
{
    //Connect to the server
    m_Context = zmq_init(1);
    m_Socket = zmq_socket(m_Context, ZMQ_PUB);
    zmq_connect(m_Socket, ServerAddress);
}
