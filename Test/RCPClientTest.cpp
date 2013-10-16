// RCClientCPP.cpp : Defines the entry point for the console application.
//

#include "RCPClient.h"
#include "RCPClientsManager.h"
#include <Windows.h>

int main()
{
	RCPClient RC;
	RC.ConnectToServer("tcp://127.0.0.1:55557");

	RC.Send("Data1", "Stream1");
	RC.Send("Data1a", "Stream1a");
	RC.PushStreamName("sub1");
	RC.Send("Data1b", "Stream1b");
	RC.PushStreamName("sub2");
	RC.Send("Data2", "Stream2");
	RC.PopStreamName();
	RC.SetThreadName("Main");
	RC.Send("Data3", "Stream3", "sdfsdf", "Win 1", 5);
	RC.PopStreamName();
	Sleep(1000);
	RC.Send("Data1", "Stream1");
	RC.Send("Data1a", "Stream1a");
	RC.PushStreamName("sub1");
	RC.Send("Data1b", "Stream1b");
	RC.PushStreamName("sub2");
	RC.Send("Data2", "Stream2");
	RC.PopStreamName();
	RC.SetThreadName("Main");
	RC.Send("Data3", "Stream3", "sdfsdf", "Win 1", 5);
	RC.PopStreamName();
	Sleep(100);

	
	RC.ConnectToServer("tcp://127.0.0.1:55557");
	int i=0;
	while(++i<5)
	{
		RC.Send("Data1", "Stream1");
		RC.Send("Data1a", "Stream1a");
		RC.PushStreamName("sub1");
		RC.Send("Data1b", "Stream1b");
		RC.PushStreamName("sub2");
		RC.Send("Data2", "Stream2");
		RC.PopStreamName();
		RC.SetThreadName("Main");
		RC.Send("Data3", "Stream3", "sdfsdf", "Win 1", 5);
		RC.PopStreamName();
		Sleep(100);
	}
	
	RC.Disconnect();

	RCPClient *pRC = RCPClientsManager::GetInstance().GetRcpClientForCurrentThread();
	pRC->ConnectToServer("tcp://127.0.0.1:55557");
	i=0;
	while(++i<5)
	{
		pRC->Send("Data1", "Stream1");
		pRC->Send("Data1a", "Stream1a");
		pRC->PushStreamName("sub1");
		pRC->Send("Data1b", "Stream1b");
		pRC->PushStreamName("sub2");
		pRC->Send("Data2", "Stream2");
		pRC->PopStreamName();
		pRC->SetThreadName("Main");
		pRC->Send("Data3", "Stream3", "sdfsdf", "Win 1", 5);
		pRC->PopStreamName();
		Sleep(1000);
	}

	pRC->Disconnect();

	return 0;
}

