// RCClientCPP.cpp : Defines the entry point for the console application.
//
#include "RCP.h"
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
	RC.Send("Data3", "Stream3");
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
	RC.Send("Data3", "Stream3");
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
		RC.Send("Data3", "Stream3", "sdfsdf");
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
		pRC->Send("Data3", "Stream3", "sdfsdf");
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
	std::vector<int> values;
	std::vector<float> valuesList;
	while(getchar())
	{
		i++;
		std::ostringstream stringStream;
		stringStream << "i=" << i;
		RC.Send(stringStream.str().c_str(), "Stream1");
		RC.Send(i, "Stream2");
		RC.Send(i*0.757, "Stream3");
		RC.Send(values);
		RC.Send(valuesList);
		RC.Send(i%3 == 0);
		values.push_back(i*i);
		valuesList.push_back(1.0/i);
		Sleep(1000);
		if(i%100 == 0)
			printf("i=%d\n", i);
	}

	RC.Disconnect();
}

void Test3()
{
	RCConnect("tcp://127.0.0.1:55557");

	int i=0;
	std::vector<int> values;
	std::vector<float> valuesList;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
		RCVar(i);
		RCVar(values);
		RCVar(valuesList);
		
		RCPrint("test1");
		RCPrint("test2", "streamA");
		RCPrint("test3", "@streamB");

		i++;
		values.push_back(i*i);
		valuesList.push_back(1.0/i);
		Sleep(1000);
		if(i%100 == 0)
			printf("i=%d\n", i);
	}

	RCDisconnect();
}

int main()
{
	//Test1();
	//Test2();
	Test3();
	return 0;
}

