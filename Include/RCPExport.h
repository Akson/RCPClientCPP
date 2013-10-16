#pragma once

#ifdef RCPCLIENT_EXPORTS
#define RCPCLIENT_API __declspec(dllexport)
#else
#define RCPCLIENT_API __declspec(dllimport)
#endif
