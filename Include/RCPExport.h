#pragma once

#ifdef RCP_STATIC
#define ZMQ_STATIC
#endif


#ifdef ZMQ_STATIC
#define RCPCLIENT_API
#else

#ifdef RCPCLIENT_EXPORTS
#define RCPCLIENT_API __declspec(dllexport)
#else
#define RCPCLIENT_API __declspec(dllimport)
#endif

#endif
