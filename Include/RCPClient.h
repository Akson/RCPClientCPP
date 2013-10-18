#pragma once
#include "RCPExport.h"
#include <vector>
#include <list>

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

	void Send(const char *value, const char *substreamName = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0);
	void Send(bool value, const char *substreamName = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0) {Send(value?"True":"False", substreamName, commands, pBinaryData, binaryDataLength);}
	template <class T> void Send(T value, const char *substreamName = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0);
	template <class T> void Send(std::vector<T> values, const char *substreamName = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0);
	template <class T> void Send(std::list<T> values, const char *substreamName = 0, const char *commands = 0, const void *pBinaryData = 0, unsigned int binaryDataLength = 0);

    void SetThreadName(const char *threadName);

    void PushStreamName(const char *substreamName);
    void PopStreamName();
	void SetStreamPrefix(const char *prefix);

private:
    RCPClientStreamsLayer *m_pImplementation;
};

#include "RCPClientDataTypes.h"