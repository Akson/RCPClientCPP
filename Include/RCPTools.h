#pragma once
#include <string>

namespace RCP
{

::std::string GetCurrentThreadIdentifier();
::std::string GetApplicationName();
::std::string GetApplicationInstanceId();
unsigned __int64 MillisecondsSince1970();

}