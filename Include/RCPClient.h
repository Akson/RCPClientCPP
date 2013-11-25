#pragma once
#include "RCPExport.h"

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
	//////////////////////////////////////////////////////////////////////////
	// NETWORK
	//////////////////////////////////////////////////////////////////////////
	
	//Connects to a give server and port. Use ZMQ format like "tcp://127.0.0.1:55557"
    void ConnectToServer(const char *ServerAddress);

    //Closes ZMQ socket and contexts (all other information is preserved)
    void Disconnect();

	//////////////////////////////////////////////////////////////////////////
	// STREAMS
	//////////////////////////////////////////////////////////////////////////

	//Set current stream name. All stream names in current stack will be added in front.
	//Use @ if this is an absolute stream name and there is no need to add streams stack.
	RCPClient& Stream(const char *stream);

	//Push/pop stream name to a streams stack. 
	//All stack components will be joined with stream separator between them.
	//This joint combination will be used as a stream name.
	void PushStreamName(const char *substreamName);
	void PopStreamName();

	//Stream prefix will be added to all stream names, even to absolute stream names starting with @.
	void SetStreamPrefix(const char *prefix);

	//////////////////////////////////////////////////////////////////////////
	// EXTRA INFO
	//////////////////////////////////////////////////////////////////////////

	//Set parameter value that will be passed to the server in a next message in JSON format
	RCPClient& Set(const char *key, const char *value);

	//Set parameter value that will be passed to the server in every message in JSON format
	void SetPermanent(const char *key, const char *value);

	//Add command to a list of commands that server should perform
	RCPClient& Command(const char *command);

	//////////////////////////////////////////////////////////////////////////
	// SENDING MESSAGES
	//////////////////////////////////////////////////////////////////////////

	//Send test data to a stream
	void Send(char *stringData);
	void Send(const char *stringData);

	//Send specified amount of binary data to a stream
	void SendBinary(void *binaryData, unsigned int binaryDataLengthInBytes);
	void SendBinary(const void *binaryData, unsigned int binaryDataLengthInBytes);
	
	//Send boolean data to a stream.
	void Send(bool value);

	//Convert value to string format and send to a stream.
	template <class T> void Send(T value);

	//Send formated (printf format) string to a stream.
	void SendFormated(const char *fmt, ...);

private:
	void SendMessageToStream(const char *substreamName, const void *messageData, size_t messgeLengthInBytes);
	void SendMessageWithAddedSystemInfo(const char *streamName, const void *messageData, size_t messageDataLengthInBytes);
	void ClearDataForNextMessage();

	RCPClientNetworkLayer *m_pNetworkLayerImplementation;
	RCPClientData *m_pData;
};

}

//This header contains templates for popular types popular data structures (vectors and lists)
#include "RCPClientDataTypes.h"
