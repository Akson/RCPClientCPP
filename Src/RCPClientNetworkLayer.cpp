#include "RCPClientNetworkLayer.h"
#include "zmq.h"

RCPClientNetworkLayer::RCPClientNetworkLayer(void)
    : m_Context(0)
{
	m_Context = zmq_init(1);
}

RCPClientNetworkLayer::~RCPClientNetworkLayer(void)
{
	CloseAllSockets();
	zmq_ctx_destroy(m_Context);
}

void RCPClientNetworkLayer::SendMessageToServer(const char *streamName, const char *stringMessage, const void *pBinaryMessageBuffer, size_t binaryMessgeLengthInBytes, unsigned long threadId)
{
	//Skip this if we don't have a server address yet
	if(m_ServerAddress.empty())
		return;

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
    int res = zmq_msg_send(&zmqMsg, GetSocketForThreadId(threadId), 0);
}

void RCPClientNetworkLayer::SetServerAddress(const char *ServerAddress)
{
	m_ServerAddress = std::string(ServerAddress);
	//Since we may change a server name when this object already exists, we need to open new sockets
	CloseAllSockets();
}

void * RCPClientNetworkLayer::GetSocketForThreadId( unsigned long threadId )
{
	auto socketIt = m_Sockets.find(threadId);
	
	if(socketIt == m_Sockets.end())
	{//There is no opened socket for this threadId yet
		void * socket = zmq_socket(m_Context, ZMQ_PUB);
		zmq_connect(socket, m_ServerAddress.c_str());
		socketIt = m_Sockets.insert(std::make_pair<unsigned long,void *>(threadId, socket)).first;
	}

	return socketIt->second;
}

void RCPClientNetworkLayer::CloseAllSockets()
{
	for(auto socketIt = m_Sockets.begin(); socketIt!=m_Sockets.end(); socketIt++)
		zmq_close(socketIt->second);
}
