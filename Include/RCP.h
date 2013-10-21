#pragma once
//Useful scripts for using Remote Console Plus

#include "RCPClientsManager.h"


#define RCConnect(ServerName) RCPClientsManager::GetRcpClientForCurrentThread()->ConnectToServer(ServerName)
#define RCDisconnect RCPClientsManager::GetRcpClientForCurrentThread()->Disconnect

#define RCVar(Variable) \
	RCPClientsManager::GetRcpClientForCurrentThread()->Send \
	(( std::string("{\"Value\":") + ConvertToString(Variable) + std::string(",\"Name\":\""#Variable"\"}")).c_str(), \
	0, "ParseJson(); Variable()")

#define RCPrint RCPClientsManager::GetRcpClientForCurrentThread()->Send
#define RCPrintf RCPClientsManager::GetRcpClientForCurrentThread()->SendFormated
