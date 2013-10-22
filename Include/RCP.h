#pragma once
//Useful scripts for using Remote Console Plus

#include "RCPClientsManager.h"

#define RCSetServerAddress(ServerName) RCP::RCPClientsManager::GetInstance().SetServerAddress(ServerName)
#define RCConnect(ServerName) RCP::RCPClientsManager::GetRcpClientForCurrentThread()->ConnectToServer(ServerName)
#define RCDisconnect RCP::RCPClientsManager::GetRcpClientForCurrentThread()->Disconnect

#define RCVar(Variable) \
	RCP::RCPClientsManager::GetRcpClientForCurrentThread()->Send \
	(( ::std::string("{\"Value\":") + ConvertToString(Variable) + ::std::string(",\"Name\":\""#Variable"\"}")).c_str(), \
	0, "ParseJson(); Variable()")

#define RCPrint RCP::RCPClientsManager::GetRcpClientForCurrentThread()->Send
#define RCPrintf RCP::RCPClientsManager::GetRcpClientForCurrentThread()->SendFormated
