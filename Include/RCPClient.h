#pragma once
#include "RCPClientSystemInfoLayer.h"

class RCPCLIENT_API RCPClient : public RCPClientSystemInfoLayer
{
public:
	RCPClient();
	~RCPClient();

private:
	//No copies
	RCPClient(RCPClient const&);
	void operator=(RCPClient const&);
};