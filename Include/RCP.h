#pragma once
//Useful scripts for using Remote Console Plus

#include "RCPClientsManager.h"

//From: http://stackoverflow.com/questions/5641427/how-to-make-preprocessor-generate-a-string-for-line-keyword
#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)

#define RCSetServerAddress(ServerName) RCP::RCPClientsManager::GetInstance().SetServerAddress(ServerName)
#define RCConnect(ServerName) RCP::RCPClientsManager::GetRcpClientForCurrentThread().ConnectToServer(ServerName)
#define RCDisconnect RCP::RCPClientsManager::GetRcpClientForCurrentThread().Disconnect

#define RC RCP::RCPClientsManager::GetRcpClientForCurrentThread().Set("FileName", __FILE__).Set("CodeLine", S__LINE__).Set("FunctionSignature", __FUNCSIG__)

#define RCVar(Variable) RC.Stream("@Vars/"#Variable"").Send(RCP::ConvertToString(Variable).c_str())

#define RCPrint RCP::RCPClientsManager::GetRcpClientForCurrentThread().Set("FileName", __FILE__).Set("CodeLine", S__LINE__).Set("FunctionSignature", __FUNCSIG__).Send
#define RCPrintf RCP::RCPClientsManager::GetRcpClientForCurrentThread().Set("FileName", __FILE__).Set("CodeLine", S__LINE__).Set("FunctionSignature", __FUNCSIG__).SendFormated

#define RCThreadGuard(ThreadName) RCP::RCPThreadGuard _rcpThreadGuard(&(RCP::RCPClientsManager::GetRcpClientForCurrentThread()), ThreadName)