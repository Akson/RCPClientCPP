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

private:
    RcpClientsStorage *m_pRCPClientsStorage;
};

}