#pragma once
#include "RCPExport.h"
#include <vector>
#include <list>


namespace RCP
{

class RCPClientNetworkLayer;
struct RCPClientData;

class RCPCLIENT_API RCPClient
{
public:
    RCPClient();
    ~RCPClient();

private: //No copying
    RCPClient(RCPClient const &);
    void operator=(RCPClient const &);

public:
    void ConnectToServer(const char *ServerAddress);

    //Closes ZMQ socket and contexts (all other information is preseved)
    void Disconnect();

	void Send(char *stringData, const char *commands = 0);
	void Send(const char *stringData, const char *commands = 0);
	void SendBinary(void *binaryData, unsigned int binaryDataLengthInBytes, const char *commands /*= 0*/);
	void SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes, const char *commands /*= 0*/);
	
	void Send(bool value, const char *commands = 0);
	template <class T> void Send(T value, const char *commands = 0);

	void SendFormated(const char *fmt, ...);

    void SetThreadName(const char *threadName);

    void PushStreamName(const char *substreamName);
    void PopStreamName();
	void SetStreamPrefix(const char *prefix);

	RCPClient& Set(const char *key, const char *value);
	RCPClient& Stream(const char *stream);
	void SendMessageToStream(const char *substreamName, const char *commands, const void *messageData, size_t messgeLengthInBytes);
	void SendMessageToSpecifiedStream(const char *absoluteStreamName, const char *commands, const void *messageData, size_t messgeLengthInBytes);
	void SendMessageWithAddedSystemInfo(const char *streamName, const char *commands, const void *messageData, size_t messageDataLengthInBytes);
private:
    RCPClientNetworkLayer *m_pNetworkLayerImplementation;
	RCPClientData *m_pData;
};

}

#include "RCPClientDataTypes.h"
