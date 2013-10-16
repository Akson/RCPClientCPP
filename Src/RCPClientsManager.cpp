#include "RCPClientsManager.h"
#include "RCPClient.h"
#include <map>


#if !defined(_WIN32) && !defined(_WIN64) // Linux - Unix
#error NON-WINDOWS version is not implemented!!!
#else // Windows and MinGW
#include <Windows.h>
inline unsigned long GetThreadId() {return GetCurrentThreadId();}
#endif


typedef unsigned long ThreadId;
struct RcpClientsStorage
{
    std::map<ThreadId, RCPClient *> m_pRcpClients;
    CRITICAL_SECTION m_CriticalSection;
};


RCPClientsManager::RCPClientsManager(void)
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
    auto &pRcpClients = m_pRCPClientsStorage->m_pRcpClients;

    EnterCriticalSection(&m_pRCPClientsStorage->m_CriticalSection);
    auto implementationIt = pRcpClients.find(threadId);
    if(implementationIt == pRcpClients.end())
    {
        //This thread does not have initialized implementation yet, so create it
        implementationIt = pRcpClients.insert(std::make_pair(threadId, new RCPClient())).first;
    }
    LeaveCriticalSection(&m_pRCPClientsStorage->m_CriticalSection);

    return implementationIt->second;
}
