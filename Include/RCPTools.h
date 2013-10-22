#pragma once
#include <string>

namespace RCP
{

unsigned long GetCurrentThreadIdentifier();
::std::string GetApplicationName();
::std::string GetApplicationInstanceId();
unsigned __int64 MillisecondsSince1970();

}