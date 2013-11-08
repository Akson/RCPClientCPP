#include "RCPTools.h"
#include <sstream>

using namespace RCP;

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

#error Some functions are not implemented for non-windows systems

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
std::string RCP::GetCurrentThreadIdentifier()
{
	std::ostringstream ss;
	ss << GetCurrentThreadId();
	return ss.str();
}

std::string RCP::GetApplicationName()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA( NULL, buffer, MAX_PATH );
	std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" )+1;
	std::string fullPath(buffer);
	return fullPath.substr( pos, fullPath.length()-pos);
}

#endif
#include <sstream>

unsigned __int64 RCP::MillisecondsSince1970()
{
	sys_time_t t;
	system_time(&t);
	return time_to_msec(t);
}

std::string RCP::GetApplicationInstanceId()
{
	//Instance identifier is the time of the first call to this function
	static unsigned long long firstCallTime = 0;
	
	if(firstCallTime == 0)
		firstCallTime = RCP::MillisecondsSince1970();

	std::string instanceIdentifier;
	std::ostringstream stringStream;
	stringStream << firstCallTime;

	return stringStream.str();
}
