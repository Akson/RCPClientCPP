#pragma once
#include "RCPExport.h"
#include <vector>
#include <list>


namespace RCP
{

class RCPClientStreamsLayer;

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

	void Send(char *stringData, const char *substreamName = 0, const char *commands = 0);
	void Send(const char *stringData, const char *substreamName = 0, const char *commands = 0);
	void SendBinary(void *binaryData, unsigned int binaryDataLengthInBytes, const char *substreamName /*= 0*/, const char *commands /*= 0*/);
	void SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes, const char *substreamName /*= 0*/, const char *commands /*= 0*/);
	
	void Send(bool value, const char *substreamName = 0, const char *commands = 0);
	template <class T> void Send(T value, const char *substreamName = 0, const char *commands = 0);

	void SendFormated(const char *fmt, ...);
	void SendFormated(const char *streamName, const char *fmt, ...);

    void SetThreadName(const char *threadName);

    void PushStreamName(const char *substreamName);
    void PopStreamName();
	void SetStreamPrefix(const char *prefix);

private:
    RCPClientStreamsLayer *m_pImplementation;
};

}

#include "RCPClientDataTypes.h"
