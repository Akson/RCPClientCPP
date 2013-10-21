#include "RCPClientSystemInfoLayer.h"
#include <sstream>
#include "json/json.h"
#include "RCPTools.h"

RCPClientSystemInfoLayer::RCPClientSystemInfoLayer(void)
    : m_EnableTimeStampSending(true)
    , m_EnableThreadIdSending(true)
    , m_EnableThreadNameSending(true)
    , m_EnableApplicationNameSending(true)
    , m_EnableInstanceIdentifierSending(true)

{
    m_ApplicationName = GetApplicationName();
    m_InstanceIdentifier = GetApplicationInstanceId();
}

RCPClientSystemInfoLayer::~RCPClientSystemInfoLayer(void)
{
}

void RCPClientSystemInfoLayer::SendMessageWithAddedSystemInfo(const char *streamName, const char *commands, const void *messageData, unsigned int messageDataLengthInBytes)
{
    unsigned long threadId = GetCurrentThreadIdentifier();

    //Write JSON string message
    Json::Value root;
    if(commands)
        root["Commands"] = commands;

    if(m_EnableTimeStampSending)
        root["TimeStampMsSince1970"] = MillisecondsSince1970();
    if(m_EnableThreadIdSending)
        root["ThreadId"] = (Json::UInt64) threadId;
    if(m_EnableThreadNameSending && !m_ThreadName.empty())
        root["ThreadName"] = m_ThreadName.c_str();
    if(m_EnableApplicationNameSending && !m_ApplicationName.empty())
        root["ApplicationName"] = m_ApplicationName.c_str();
    if(m_EnableInstanceIdentifierSending && !m_InstanceIdentifier.empty())
        root["InstanceIdentifier"] = m_InstanceIdentifier.c_str();

    Json::FastWriter writer;
    std::string messageInfoJson = writer.write(root);

    //Send ZMQ message to the server
    SendMessageToServer(streamName, messageInfoJson.c_str(), messageData, messageDataLengthInBytes);
}

void RCPClientSystemInfoLayer::SetThreadName(const char *threadName)
{
    m_ThreadName = std::string(threadName);
}
