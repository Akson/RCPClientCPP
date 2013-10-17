#include "RCPClientSystemInfoLayer.h"
#include <sstream>
#include "json/json.h"
#include "RCPTools.h"

RCPClientSystemInfoLayer::RCPClientSystemInfoLayer(void)
{
	m_ApplicationName = GetApplicationName();
	m_InstanceIdentifier = GetApplicationInstanceId();
}

RCPClientSystemInfoLayer::~RCPClientSystemInfoLayer(void)
{
}

void RCPClientSystemInfoLayer::SendMessageWithAddedSystemInfo(const char *value, const char *streamName, const char *commands, const void *pBinaryData, unsigned int binaryDataLength)
{
    unsigned long threadId = GetCurrentThreadIdentifier();

    //Write JSON string message
    Json::Value root;

    root["TimeStampMsSince1970"] = MillisecondsSince1970();
    root["Value"] = value;
    root["ThreadId"] = (Json::UInt64) threadId;
    if(commands) root["Commands"] = commands;
	if(!m_ThreadName.empty()) root["ThreadName"] = m_ThreadName.c_str();
	if(!m_ApplicationName.empty()) root["ApplicationName"] = m_ApplicationName.c_str();
	if(!m_InstanceIdentifier.empty()) root["InstanceIdentifier"] = m_InstanceIdentifier.c_str();

    Json::StyledWriter writer;
    std::string jsonMsg = writer.write(root);

    //Send ZMQ message to the server
    SendMessageToServer(streamName, jsonMsg.c_str(), pBinaryData, binaryDataLength);
}

void RCPClientSystemInfoLayer::SetThreadName(const char *threadName)
{
    m_ThreadName = std::string(threadName);
}
