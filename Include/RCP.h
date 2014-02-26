#pragma once
//Useful scripts for using Remote Console Plus

#include "RCPClientsManager.h"
#include "PerformanceTimer.h"

//From: http://stackoverflow.com/questions/5641427/how-to-make-preprocessor-generate-a-string-for-line-keyword
#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)


#define RCSetServerAddress(ServerName) RCP::RCPClientsManager::GetInstance().SetServerAddress(ServerName)
#define RCConnect(ServerName) RCP::RCPClientsManager::GetRcpClientForCurrentThread().ConnectToServer(ServerName)
#define RCDisconnect RCP::RCPClientsManager::GetRcpClientForCurrentThread().Disconnect
#define RCThreadGuard(ThreadName) RCP::RCPThreadGuard _rcpThreadGuard(&(RCP::RCPClientsManager::GetRcpClientForCurrentThread()), ThreadName)

#define RC RCP::RCPClientsManager::GetRcpClientForCurrentThread().Set("FileName", __FILE__).Set("CodeLine", S__LINE__).Set("FunctionSignature", __FUNCSIG__)


#define RCPrint RC.Send
#define RCPrintText RC.Set("ProcessingSequence", "_Text").SendFormated
#define RCPrintHtml RC.Set("ProcessingSequence", "_Html").SendFormated
#define RCPrintJson RC.Set("ProcessingSequence", "_Json").Set("DataType", "JSON").SendFormated
#define RCPrintVariable(Variable) RC.Set("ProcessingSequence", "_Var").Set("VariableName", ""#Variable"").Send(Variable)

#define RCPrintf RCPrintText
#define RCPrinth RCPrintHtml
#define RCPrintj RCPrintJson
#define RCVar RCPrintVariable

#define RCP_SCOPE_BLOCK(name) RCP::RCScopeBlock _RCP_SCOPE_BLOCK(name)