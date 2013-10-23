#pragma once
#include "RCPClientNetworkLayer.h"
#include <string>
#include <map>

namespace RCP
{

class RCPClientSystemInfoLayer : public RCPClientNetworkLayer
{
public:
    RCPClientSystemInfoLayer();
    ~RCPClientSystemInfoLayer();

    void SetThreadName(const char *threadName);
	void SetExtraData(const char *key, const char *value);

protected:
    void SendMessageWithAddedSystemInfo(const char *streamName, const char *commands, const void *messageData, size_t messageDataLengthInBytes);

private:
    ::std::string m_ThreadName;//Thread alias name
	::std::string m_ApplicationName;
	::std::string m_InstanceIdentifier;

	bool m_EnableTimeStampSending;
	bool m_EnableThreadIdSending;
	bool m_EnableThreadNameSending;
	bool m_EnableApplicationNameSending;
	bool m_EnableInstanceIdentifierSending;

	::std::map<::std::string, ::std::string> m_ExtraData;
};

}