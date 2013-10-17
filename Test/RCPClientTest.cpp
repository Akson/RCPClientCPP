// RCClientCPP.cpp : Defines the entry point for the console application.
//

#include "RCPClient.h"
#include "RCPClientsManager.h"
#include <Windows.h>
#include <sstream>

void Test1()
{
	RCPClient RC;
	RC.ConnectToServer("tcp://127.0.0.1:55557");
	Sleep(1000);

	RC.Send("111111111111111111===========================================");
	RC.Send("Data1");
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
	RC.Send("222222222222222222222222222===========================================");
	Sleep(100);


	RC.ConnectToServer("tcp://127.0.0.1:55557");
	Sleep(1000);
	RC.Send("2.52.52.52.52.52.52.52.52.52.52.52.5===========================================");
	int i=0;
	while(++i<2500)
	{
		RC.PushStreamName("sub2");
		RC.Send("Data1", "Stream1");
		RC.Send("Data1a", "Stream1a");
		RC.PushStreamName("sub1");
		RC.Send("Data1b", "Stream1b");
		RC.Send("Data1b", "@AbsoluteStream");
		RC.PushStreamName("sub2");
		RC.Send("Data2");
		RC.PopStreamName();
		RC.SetThreadName("Main");
		RC.Send("Data3", "Stream3", "sdfsdf", "Win 1", 5);
		RC.PopStreamName();
		Sleep(300);
	}

	RC.Send("3333333333333333333333333333===========================================");
	RC.Disconnect();

	RCPClient *pRC = RCPClientsManager::GetInstance().GetRcpClientForCurrentThread();
	pRC->ConnectToServer("tcp://127.0.0.1:55557");
	RC.Send("*************************************************************");
	RC.Send("*************************************************************");
	RC.Send("*************************************************************");
	RC.Send("*************************************************************");
	RC.Send("*************************************************************");
	Sleep(1000);
	i=0;
	pRC->Send("44444444444444444444444444444===========================================");
	pRC->SetStreamPrefix("");
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

	pRC->Send("5555555555555555555555555555===========================================");
	pRC->Disconnect();
}

void Test2()
{
	RCPClient RC;
	RC.ConnectToServer("tcp://127.0.0.1:55557");
	Sleep(1000);

	int i=0;
	while(true)
	{
		i++;
		std::ostringstream stringStream;
		stringStream << "i=" << i;
		RC.Send(stringStream.str().c_str(), "Stream1");
		Sleep(1000);
		if(i%1000 == 0)
			printf("i=%d\n", i);
	}

	RC.Disconnect();
}

int main()
{
	//Test1();
	Test2();
	return 0;
}

