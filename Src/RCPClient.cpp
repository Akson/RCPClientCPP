#include "RCPClient.h"

#include "json/json.h"
#include "zmq.h"

#include <Windows.h>
#include <sstream>

RCPClient::RCPClient(void)
	: m_StartTime(0)
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

void RCPClient::Print(const char* Value, const char* StreamName, const char* Commands, const void* pBinaryData, unsigned int binaryDataLength)
{
	//Write JSON string message
	Json::Value root;

	root["TimeStamp"] = (Json::UInt64)GenerateLocalTimeStamp();
	if(Value) root["Value"] = Value;
	if(Commands) root["Commands"] = Commands;

	Json::StyledWriter writer;
	std::string jsonMsg = writer.write(root);

	//Send ZMQ message to the server
	SendMessageToServer(StreamName, jsonMsg.c_str(), pBinaryData, binaryDataLength);
}

