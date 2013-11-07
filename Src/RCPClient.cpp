#include "RCPClient.h"
#include "RCPClientNetworkLayer.h"
#include <stdarg.h>
#include "RCPTools.h"
#include "json/json.h"

using namespace RCP;

struct RCP::RCPClientData
{
    std::vector<::std::string> m_SubstreamNamesStack;
    std::string m_SubstreamsSeparator;
    std::string m_ConstantPrefix;
    std::string m_StreamNameForNextMessage;
    std::string m_ThreadName;//Thread alias name
    std::string m_ApplicationName;
    std::string m_InstanceIdentifier;
    std::map<std::string, std::string> m_ExtraData;
};

RCPClient::RCPClient(void)
    : m_pNetworkLayerImplementation(0)
{
    m_pNetworkLayerImplementation = new RCP::RCPClientNetworkLayer();
    m_pData = new RCPClientData;

    m_pData->m_SubstreamsSeparator = "/";
    m_pData->m_ApplicationName = GetApplicationName();
    m_pData->m_InstanceIdentifier = GetApplicationInstanceId();

    std::ostringstream stringStream;
    stringStream << "[";
    stringStream << GetApplicationName();
    stringStream << "]";
    m_pData->m_ConstantPrefix = stringStream.str();

    PushStreamName("StdOut");
}

RCPClient::~RCPClient(void)
{
    delete(m_pNetworkLayerImplementation);
}

void RCPClient::ConnectToServer(const char *ServerAddress)
{
    m_pNetworkLayerImplementation->ConnectToServer(ServerAddress);
}

void RCPClient::SetThreadName(const char *threadName)
{
    m_pData->m_ThreadName = threadName;
}

void RCPClient::PushStreamName(const char *substreamName)
{
    m_pData->m_SubstreamNamesStack.push_back(substreamName);
}

void RCPClient::PopStreamName()
{
    m_pData->m_SubstreamNamesStack.erase(m_pData->m_SubstreamNamesStack.end() - 1);
}

void RCPClient::Disconnect()
{
    m_pNetworkLayerImplementation->Disconnect();
}

void RCPClient::SetStreamPrefix(const char *prefix)
{
    m_pData->m_ConstantPrefix = prefix;
}

void RCPClient::Send(const char *stringData, const char *commands /*= 0*/)
{
    SendMessageToStream(0, commands, stringData, strlen(stringData));
}

void RCPClient::Send(char *stringData, const char *commands /*= 0*/)
{
    SendMessageToStream(0, commands, stringData, strlen(stringData));
}

void RCPClient::SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes, const char *commands /*= 0*/)
{
    SendMessageToStream(0, commands, binaryData, binaryDataLengthInBytes);
}

void RCPClient::SendBinary(void *binaryData, unsigned int binaryDataLengthInBytes, const char *commands /*= 0*/)
{
    SendMessageToStream(0, commands, binaryData, binaryDataLengthInBytes);
}

void RCPClient::Send(bool value, const char *commands /*= 0*/)
{
    Send(
        value ? "{\"Value\":true}" : "{\"Value\":false}",
        commands ? (std::string("ParseJson();") + std::string(commands)).c_str() : "ParseJson()"
    );
}

void RCPClient::SendFormated(const char *fmt, ...)
{
    char buffer[4096];

    //Just copy output to a standard console for now.
    int res;
    va_list ap;
    va_start(ap, fmt);
    res = vsprintf_s(buffer, fmt, ap);
    va_end(ap);

    Send(buffer);
}

RCPClient &RCP::RCPClient::Set(const char *key, const char *value)
{
    m_pData->m_ExtraData[key] = value;
    return *this;
}

RCPClient &RCP::RCPClient::Stream(const char *stream)
{
    m_pData->m_StreamNameForNextMessage = stream;
    return *this;
}

void RCP::RCPClient::SendMessageToStream(const char *substreamName, const char *commands, const void *messageData, size_t messgeLengthInBytes)
{
    if(substreamName == 0)
        substreamName = m_pData->m_StreamNameForNextMessage.c_str();

    //If substream name starts with @ symbol, it is threated as a full stream name
    if(substreamName && substreamName[0] == '@')
        return SendMessageToSpecifiedStream(substreamName + 1, commands, messageData, messgeLengthInBytes);

    std::string streamName = m_pData->m_ConstantPrefix;
    if(!m_pData->m_ConstantPrefix.empty()) streamName += m_pData->m_SubstreamsSeparator;
    for(auto substreamNameIt = m_pData->m_SubstreamNamesStack.begin(); substreamNameIt != m_pData->m_SubstreamNamesStack.end(); substreamNameIt++)
    {
        if(substreamNameIt != m_pData->m_SubstreamNamesStack.begin())
            streamName += m_pData->m_SubstreamsSeparator;
        streamName += *substreamNameIt;
    }

    if(substreamName && strlen(substreamName))
    {
        if(m_pData->m_SubstreamNamesStack.size() > 0)
            streamName += m_pData->m_SubstreamsSeparator;
        streamName.append(substreamName);
    }

    SendMessageWithAddedSystemInfo(streamName.c_str(), commands, messageData, messgeLengthInBytes);

    m_pData->m_StreamNameForNextMessage.clear();
}

void RCP::RCPClient::SendMessageToSpecifiedStream(const char *absoluteStreamName, const char *commands, const void *messageData, size_t messgeLengthInBytes)
{
    if(absoluteStreamName == 0)
        absoluteStreamName = m_pData->m_StreamNameForNextMessage.c_str();

    std::string streamName = m_pData->m_ConstantPrefix;
    if(!m_pData->m_ConstantPrefix.empty()) streamName += m_pData->m_SubstreamsSeparator;
    streamName += absoluteStreamName;
    SendMessageWithAddedSystemInfo(streamName.c_str(), commands, messageData, messgeLengthInBytes);

    m_pData->m_StreamNameForNextMessage.clear();
}

void RCP::RCPClient::SendMessageWithAddedSystemInfo(const char *streamName, const char *commands, const void *messageData, size_t messageDataLengthInBytes)
{
    unsigned long threadId = GetCurrentThreadIdentifier();

    //Write JSON string message
    Json::Value root;

    for(auto mapIt = m_pData->m_ExtraData.begin(); mapIt != m_pData->m_ExtraData.end(); mapIt++)
        root[mapIt->first.c_str()] = mapIt->second.c_str();

    if(commands)
        root["Commands"] = commands;

    root["TimeStampMsSince1970"] = MillisecondsSince1970();
    root["ThreadId"] = (Json::UInt64) threadId;
    root["ThreadName"] = m_pData->m_ThreadName.c_str();
    root["ApplicationName"] = m_pData->m_ApplicationName.c_str();
    root["InstanceIdentifier"] = m_pData->m_InstanceIdentifier.c_str();

    Json::FastWriter writer;
    std::string messageInfoJson = writer.write(root);

    //Send ZMQ message to the server
    m_pNetworkLayerImplementation->SendMessageToServer(streamName, messageInfoJson.c_str(), messageData, messageDataLengthInBytes);

    //All extra data are passed, new data will be added later
    m_pData->m_ExtraData.clear();
}
