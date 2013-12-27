#pragma once
#include "RCPExport.h"
#include "RCPClient.h"
#include <memory>

namespace RCP
{

struct RcpClientsStorage;

class RCPCLIENT_API RCPClientsManager
{
    //////////////////////////////////////////////////////////////////////////
    //SINGLETON
public:
    static RCPClientsManager &GetInstance()
    {
        static RCPClientsManager instance;
        return instance;
    }
private:
    RCPClientsManager();
    ~RCPClientsManager();
    RCPClientsManager(RCPClientsManager const &);
    void operator=(RCPClientsManager const &);
    //SINGLETON
    //////////////////////////////////////////////////////////////////////////

public:
	static RCPClient &GetRcpClientForCurrentThread();
	void SetServerAddress(const char *serverName);

private:
	std::unique_ptr<RcpClientsStorage> m_pRCPClientsStorage;
	std::string m_DefaultServerAddreess;
};

class RCPCLIENT_API RCPThreadGuard
{
public:
	RCPThreadGuard(RCPClient *pRCPClient, const char *threadName)
		:m_pRCPClient(pRCPClient)
	{
		pRCPClient->Set("ThreadName", threadName, true);
	}
	~RCPThreadGuard()
	{
		m_pRCPClient->Disconnect();
	}
private:
	RCPThreadGuard(RCPThreadGuard const &);
	void operator=(RCPThreadGuard const &);
	RCPClient *m_pRCPClient;
};

}