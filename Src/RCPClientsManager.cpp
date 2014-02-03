#include "RCPClientsManager.h"
#include "RCPClient.h"
#include <map>
#include <thread>
#include <mutex>

#include <sstream>
#include <chrono>

using namespace RCP;

#if !defined(_WIN32) && !defined(_WIN64) // Linux - Unix
#else // Windows and MinGW
#include <Windows.h>
std::string GetApplicationName()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/") + 1;
    std::string fullPath(buffer);
    return fullPath.substr(pos, fullPath.length() - pos);
}
#endif

std::string GetApplicationInstanceId()
{
    //Instance identifier is the time of the first call to this function
    static unsigned long long firstCallTime = 0;

    if(firstCallTime == 0)
        firstCallTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::string instanceIdentifier;
    std::ostringstream stringStream;
    stringStream << firstCallTime;

    return stringStream.str();
}

std::string GetThreadIdString()
{
    std::ostringstream stringStream;
    stringStream << std::this_thread::get_id();
    return stringStream.str();
}


struct RCP::RcpClientsStorage
{
    std::map<std::thread::id, std::unique_ptr<RCPClient>> m_pRcpClients;
    std::mutex m_pRcpClientsMutex;
};


RCPClientsManager::RCPClientsManager(void)
    : m_pRCPClientsStorage(new RcpClientsStorage)
// 	, m_DefaultServerAddreess("tcp://127.0.0.1:55557")
{
}

RCPClientsManager::~RCPClientsManager(void)
{
}

RCPClient &RCPClientsManager::GetRcpClientForCurrentThread()
{
    std::thread::id threadId = std::this_thread::get_id();
    auto &instance = RCPClientsManager::GetInstance();
    auto &storage = instance.m_pRCPClientsStorage;
    auto &rcpClients = storage->m_pRcpClients;

    storage->m_pRcpClientsMutex.lock();
    auto clientIt = rcpClients.find(threadId);
    if(clientIt == rcpClients.end())
    {
        std::unique_ptr<RCPClient> pRCPClient(new RCPClient());

        pRCPClient->Set("ApplicationName", GetApplicationName().c_str(), true);
        pRCPClient->Set("InstanceIdentifier", GetApplicationInstanceId().c_str(), true);
        pRCPClient->Set("ThreadId", GetThreadIdString().c_str(), true);
        pRCPClient->Set("ProcessingSequence", "_Text", true);
        pRCPClient->PushStreamName("#");

        //This thread does not have initialized implementation yet, so create it
        clientIt = rcpClients.insert(std::make_pair(threadId, std::move(pRCPClient))).first;
        //Connect to default server when a new thread is created
        if(instance.m_DefaultServerAddreess.size() > 0)
            clientIt->second->ConnectToServer(instance.m_DefaultServerAddreess.c_str());
    }
    storage->m_pRcpClientsMutex.unlock();

    return *(clientIt->second);
}

void RCP::RCPClientsManager::SetServerAddress(const char *serverName)
{
    RCPClientsManager::GetInstance().m_DefaultServerAddreess = serverName;
}
