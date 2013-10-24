#pragma once
#include "RCPExport.h"
#include "RCPClient.h"

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
	void SetServerAddress(const char *pServerName);

private:
    RcpClientsStorage *m_pRCPClientsStorage;
	::std::string m_DefaultServerAddreess;
};

class RCPCLIENT_API RCPThreadGuard
{
public:
	RCPThreadGuard(RCPClient *pRCPClient, const char *threadName)
	{
		pRCPClient->SetThreadName(threadName);
		m_pRCPClient = pRCPClient;
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