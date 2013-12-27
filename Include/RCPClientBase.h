#pragma once
#include "RCPClientNetworkLayer.h"
#include <memory>
#include <vector>
#include <map>
#include <chrono>

namespace RCP
{

struct RCPClientData;

class RCPClientBase : public RCPClientNetworkLayer
{
public:
    RCPClientBase();
    virtual ~RCPClientBase();

    void SetValueForNextMessage(const std::string &key, const std::string &value, bool permanent = false);

    //Push/pop stream name to a streams stack.
    //All stack components will be joined with stream separator between them.
    //This joint combination will be used as a stream name.
    void PushStreamName(const std::string &substreamName);
    void PopStreamName();

protected:
    void SendMessageToStream(const char *substreamName, const void *messageData, size_t messgeLengthInBytes);
    void SendMessageWithAddedSystemInfo(const char *streamName, const void *messageData, size_t messageDataLengthInBytes);
    void ClearDataForNextMessage();

    std::unique_ptr<RCPClientData> m_pData;
};

}