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
#define RCThreadGuard(ThreadName) RCP::RCPThreadGuard _rcpThreadGuard(&(RCP::RCPClientsManager::GetRcpClientForCurrentThread()), ThreadName)

#define RC RCP::RCPClientsManager::GetRcpClientForCurrentThread().Set("FileName", __FILE__).Set("CodeLine", S__LINE__).Set("FunctionSignature", __FUNCSIG__)


#define RCPrint RC.Send
#define RCPrintText RC.Stream("@_TextOut").SendFormated
#define RCPrintHtml RC.Stream("@_HtmlOut").SendFormated
#define RCPrintJson RC.Set("DataType", "JSON").Stream("@_JsonOut").SendFormated
#define RCPrintVariable(Variable) RC.Stream("@_VarOut").Set("VariableName", ""#Variable"").Send(RCP::ConvertToString(Variable).c_str())

#define RCPrintf RCPrintText
#define RCPrinth RCPrintHtml
#define RCPrintj RCPrintJson
#define RCVar RCPrintVariable
