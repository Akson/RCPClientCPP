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
    static RCPClient *GetRcpClientForCurrentThread();
	void SetServerAddress(const char *pServerName);

private:
    RcpClientsStorage *m_pRCPClientsStorage;
	::std::string m_DefaultServerAddreess;
};

}