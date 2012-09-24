#include "RCPClient.h"

#include "json/json.h"
#include "zmq.h"

#include <Windows.h>
#include <sstream>

RCPClient::RCPClient(void)
	: m_StartTime(0)
	, m_Context(0)
	, m_Socket(0)
{
	//Save start time for generating local timestamps
	m_StartTime = GetTickCount();
}

RCPClient::~RCPClient(void)
{
}

unsigned long RCPClient::GenerateLocalTimeStamp()
{
	return GetTickCount() - m_StartTime;
}

void RCPClient::SendMessageToServer(const char* Value, const char* StreamName, const char* Filters, const char* Destinations, const void* pBinaryData, unsigned int binaryDataLength)
{
	//Send message only if we are connected
	if(m_Socket == 0) return;

	//Create JSON object
	Json::Value root;

	root["TimeStamp"] = (Json::UInt64)GenerateLocalTimeStamp();
	if(Value) root["Value"] = Value;
	if(StreamName) root["StreamName"] = StreamName;
	if(Filters) root["Filters"] = Filters;
	if(Destinations) root["Destinations"] = Destinations;

	//Write JSON string message
	Json::StyledWriter writer;
	std::string jsonMsg = writer.write(root);

	//Create ZMQ message
	zmq_msg_t zmqMsg;
	zmq_msg_init_size(&zmqMsg, jsonMsg.length());
	memcpy (zmq_msg_data (&zmqMsg), jsonMsg.c_str(), jsonMsg.length());
	
	//Send ZMQ message to the server
	int res = zmq_send(m_Socket, &zmqMsg, 0);
}

void RCPClient::Print(const char* Value, const char* StreamName, const char* Filters, const char* Destinations)
{
	SendMessageToServer(Value, StreamName, Filters, Destinations, 0, 0);
}

void RCPClient::ConnectToServer( const char* ServerAddress )
{
	//Connect to the server
	m_Context = zmq_init(1);
	m_Socket = zmq_socket(m_Context, ZMQ_PUB);
	zmq_connect(m_Socket, ServerAddress);
}
