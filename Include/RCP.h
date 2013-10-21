#pragma once
//Useful scripts for using Remote Console Plus

#include "RCPClientsManager.h"


#define RCConnect(ServerName) RCPClientsManager::GetRcpClientForCurrentThread()->ConnectToServer(ServerName)
#define RCDisconnect RCPClientsManager::GetRcpClientForCurrentThread()->Disconnect

#define RCVar(Variable) RCPClientsManager::GetRcpClientForCurrentThread()->Send(Variable, 0, "VariableName("#Variable")")
#define RCVar2Stream(Variable, Stream) RCPClientsManager::GetRcpClientForCurrentThread()->Send(Variable, Stream, "VariableName("#Variable")")
#define RCPrint RCPClientsManager::GetRcpClientForCurrentThread()->Send
