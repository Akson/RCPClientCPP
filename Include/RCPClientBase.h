#pragma once
#include "RCPClientNetworkLayer.h"
#include "RCPExport.h"
#include <memory>
#include <string>

namespace RCP
{

struct RCPClientData;

class RCPCLIENT_API RCPClientBase : public RCPClientNetworkLayer
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
    void PreprareAndSendMessage(const void *messageData, size_t messgeLengthInBytes);
    void ClearDataForNextMessage();

    std::unique_ptr<RCPClientData> m_pData;
};

}