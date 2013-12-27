#pragma once
#include "RCPExport.h"
#include "RCPClientBase.h"

namespace RCP
{

	class RCPCLIENT_API RCPClient : public RCPClientBase
{
public:
    RCPClient();
    ~RCPClient();

private: //No copying
    RCPClient(RCPClient const &);
    void operator=(RCPClient const &);

public:
	//////////////////////////////////////////////////////////////////////////
	// STREAMS
	//////////////////////////////////////////////////////////////////////////

	//Set current stream name. All stream names in current stack will be added in front.
	//Use @ if this is an absolute stream name and there is no need to add streams stack.
	RCPClient& Stream(const std::string &stream);


	//////////////////////////////////////////////////////////////////////////
	// EXTRA INFO
	//////////////////////////////////////////////////////////////////////////

	//Set parameter value that will be passed to the server in a next message in JSON format
	RCPClient& Set(const char *key, const std::string &value, bool permanent = false);
	RCPClient& Set(const char *key, int value, bool permanent = false);
	RCPClient& Set(const char *key, float value, bool permanent = false);

	//////////////////////////////////////////////////////////////////////////
	// SENDING MESSAGES
	//////////////////////////////////////////////////////////////////////////

	//Send test data to a stream
	void Send(const char *stringData);

	//Send specified amount of binary data to a stream
	void SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes);
	
	//Send boolean data to a stream.
	void Send(bool value);

	//Convert value to string format and send to a stream.
	template <class T> void Send(T value);

	//Send formated (printf format) string to a stream.
	void SendFormated(const char *fmt, ...);
};

}

//This header contains templates for popular types popular data structures (vectors and lists)
#include "RCPClientDataTypes.h"
