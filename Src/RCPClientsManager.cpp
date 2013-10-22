#include "RCPClientsManager.h"
#include "RCPClient.h"
#include <map>

using namespace RCP;

#if !defined(_WIN32) && !defined(_WIN64) // Linux - Unix
#error NON-WINDOWS version is not implemented!!!
#else // Windows and MinGW
#include <Windows.h>
inline unsigned long GetCurrentThreadIdentifier() {return GetCurrentThreadId();}
#endif


typedef unsigned long ThreadId;
struct RCP::RcpClientsStorage
{
    std::map<ThreadId, RCPClient *> m_pRcpClients;
    CRITICAL_SECTION m_CriticalSection;
};


RCPClientsManager::RCPClientsManager(void)
	:m_pRCPClientsStorage(NULL)
{
    m_pRCPClientsStorage = new RcpClientsStorage();
    InitializeCriticalSectionAndSpinCount(&m_pRCPClientsStorage->m_CriticalSection, 0);
}

RCPClientsManager::~RCPClientsManager(void)
{
    for(auto it = m_pRCPClientsStorage->m_pRcpClients.begin(); it != m_pRCPClientsStorage->m_pRcpClients.end(); it++)
        delete(it->second);
    DeleteCriticalSection(&m_pRCPClientsStorage->m_CriticalSection);
    delete(m_pRCPClientsStorage);
}

RCPClient *RCPClientsManager::GetRcpClientForCurrentThread()
{
    ThreadId threadId = GetCurrentThreadId();
    auto &pRcpClients = RCPClientsManager::GetInstance().m_pRCPClientsStorage->m_pRcpClients;

    EnterCriticalSection(&(RCPClientsManager::GetInstance().m_pRCPClientsStorage->m_CriticalSection));
    auto implementationIt = pRcpClients.find(threadId);
    if(implementationIt == pRcpClients.end())
    {
        //This thread does not have initialized implementation yet, so create it
        implementationIt = pRcpClients.insert(std::make_pair(threadId, new RCPClient())).first;
		//Connect to default server when a new thread is created
		if(RCPClientsManager::GetInstance().m_DefaultServerAddreess.size()>0) 
			implementationIt->second->ConnectToServer(RCPClientsManager::GetInstance().m_DefaultServerAddreess.c_str());
    }
    LeaveCriticalSection(&(RCPClientsManager::GetInstance().m_pRCPClientsStorage->m_CriticalSection));

    return implementationIt->second;
}

void RCP::RCPClientsManager::SetServerAddress( const char *pServerName )
{
	RCPClientsManager::GetInstance().m_DefaultServerAddreess = ::std::string(pServerName);
}
