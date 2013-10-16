#include "RCPClientSystemInfoLayer.h"
#include "json/json.h"

#if !defined(_WIN32) && !defined(_WIN64) // Linux - Unix

#include <sys/time.h>
typedef timeval sys_time_t;
inline void system_time(sys_time_t *t)
{
	gettimeofday(t, NULL);
}

inline unsigned __int64 time_to_msec(const sys_time_t &t)
{
	return t.tv_sec * 1000LL + t.tv_usec / 1000;
}

#else // Windows and MinGW

#include <sys/timeb.h>
typedef _timeb sys_time_t;
inline void system_time(sys_time_t *t) 
{ 
	_ftime64_s(t); 
}

inline unsigned __int64 time_to_msec(const sys_time_t &t)
{
	return t.time * 1000LL + t.millitm;
}

#include <Windows.h>
inline unsigned long GetThreadId()
{
	return GetCurrentThreadId();
}

#endif

inline unsigned __int64 MillisecondsSince1970()
{
	sys_time_t t;
	system_time(&t);
	return time_to_msec(t);
}

RCPClientSystemInfoLayer::RCPClientSystemInfoLayer(void)
{
}

RCPClientSystemInfoLayer::~RCPClientSystemInfoLayer(void)
{
}

void RCPClientSystemInfoLayer::PushToStreamWithAddedSystemInfo(const char *value, const char *streamName, const char *commands, const void *pBinaryData, unsigned int binaryDataLength)
{
	unsigned long threadId = GetThreadId();

    //Write JSON string message
    Json::Value root;

    root["TimeStampMsSince1970"] = MillisecondsSince1970();
    root["Value"] = value;
	root["ThreadId"] = (Json::UInt64) threadId;
    if(commands) root["Commands"] = commands;

	auto nameIt = m_ThreadNames.find(threadId);
	if(nameIt != m_ThreadNames.end())
		root["ThreadName"] = nameIt->second.c_str();

    Json::StyledWriter writer;
    std::string jsonMsg = writer.write(root);

    //Send ZMQ message to the server
    SendMessageToServer(streamName, jsonMsg.c_str(), pBinaryData, binaryDataLength, threadId);
}

void RCPClientSystemInfoLayer::SetThreadName( const char* threadName )
{
	m_ThreadNames[GetThreadId()] = std::string(threadName);
}
