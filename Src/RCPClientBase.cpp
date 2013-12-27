#include "RCPClientBase.h"

#include "json/json.h"

using namespace RCP;

struct RCP::RCPClientData
{
	std::string m_SubstreamsSeparator;
	std::vector<::std::string> m_SubstreamNamesStack;
	std::map<std::string, std::string> m_ExtraData;
	std::map<std::string, std::string> m_PermanentExtraData;
};

RCPClientBase::RCPClientBase()
    : m_pData(new RCPClientData)
{
    m_pData->m_SubstreamsSeparator = "/";
}


RCPClientBase::~RCPClientBase()
{
}

void RCPClientBase::SetValueForNextMessage(const std::string &key, const std::string &value, bool permanent)
{
    if(permanent)
        m_pData->m_PermanentExtraData[key] = value;
    else
        m_pData->m_ExtraData[key] = value;
}

void RCPClientBase::PushStreamName(const std::string &substreamName)
{
	m_pData->m_SubstreamNamesStack.push_back(substreamName);
}

void RCPClientBase::PopStreamName()
{
	m_pData->m_SubstreamNamesStack.erase(m_pData->m_SubstreamNamesStack.end() - 1);
}

void RCPClientBase::SendMessageToStream(const void *messageData, size_t messgeLengthInBytes)
{
    //Do nothing if there is no connection to a server
    if(!IsConnected())
    {
        ClearDataForNextMessage();
        return;
    }

	std::string streamNameForNextMessage;
	auto it = m_pData->m_ExtraData.find("Stream");
	if(it != m_pData->m_ExtraData.end())
		streamNameForNextMessage = it->second;

	const char *substreamName = streamNameForNextMessage.c_str();

    //If substream name starts with @ symbol, it is threated as a full stream name
    std::string streamName;
	for(auto substreamNameIt = m_pData->m_SubstreamNamesStack.begin(); substreamNameIt != m_pData->m_SubstreamNamesStack.end(); substreamNameIt++)
	{
		if(substreamNameIt != m_pData->m_SubstreamNamesStack.begin())
			streamName += m_pData->m_SubstreamsSeparator;
		streamName += *substreamNameIt;
	}

	if(streamNameForNextMessage.length()>0)
    {
		if(streamNameForNextMessage[0] == '@')
			streamName = streamNameForNextMessage;
		else
		{
			if(streamName.length() > 0)
				streamName += m_pData->m_SubstreamsSeparator;
			streamName += streamNameForNextMessage;
		}
    }
    SendMessageWithAddedSystemInfo(streamName.c_str(), messageData, messgeLengthInBytes);
}

void RCPClientBase::SendMessageWithAddedSystemInfo(const char *streamName, const void *messageData, size_t messageDataLengthInBytes)
{
    //Write JSON string message
    Json::Value root;

    for(auto mapIt = m_pData->m_PermanentExtraData.begin(); mapIt != m_pData->m_PermanentExtraData.end(); mapIt++)
        root[mapIt->first.c_str()] = mapIt->second.c_str();

    for(auto mapIt = m_pData->m_ExtraData.begin(); mapIt != m_pData->m_ExtraData.end(); mapIt++)
        root[mapIt->first.c_str()] = mapIt->second.c_str();

    root["TimeStampMsSince1970"] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    Json::FastWriter writer;
    std::string messageInfoJson = writer.write(root);

    //Send ZMQ message to the server
    SendMessageToServer(streamName, messageInfoJson.c_str(), messageData, messageDataLengthInBytes);

    //All extra data are passed, new data will be added later
    ClearDataForNextMessage();
}

void RCPClientBase::ClearDataForNextMessage()
{
    m_pData->m_ExtraData.clear();
}
