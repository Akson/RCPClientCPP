// RCClientCPP.cpp : Defines the entry point for the console application.
//
#include "RCP.h"
#include <Windows.h>
#include <sstream>

void Test1()
{
	RCP::RCPClient rc;
	rc.ConnectToServer("tcp://127.0.0.1:55557");
	Sleep(1000);

	rc.Send("111111111111111111===========================================");
	rc.Send("Data1");
	rc.Send("Data1a", "Stream1a");
	rc.PushStreamName("sub1");
	rc.Send("Data1b", "Stream1b");
	rc.PushStreamName("sub2");
	rc.Send("Data2", "Stream2");
	rc.PopStreamName();
	rc.SetThreadName("Main");
	rc.Send("Data3", "Stream3");
	rc.PopStreamName();
	Sleep(1000);
	rc.Send("Data1", "Stream1");
	rc.Send("Data1a", "Stream1a");
	rc.PushStreamName("sub1");
	rc.Send("Data1b", "Stream1b");
	rc.PushStreamName("sub2");
	rc.Send("Data2", "Stream2");
	rc.PopStreamName();
	rc.SetThreadName("Main");
	rc.Send("Data3", "Stream3");
	rc.PopStreamName();
	rc.Send("222222222222222222222222222===========================================");
	Sleep(100);


	rc.ConnectToServer("tcp://127.0.0.1:55557");
	Sleep(1000);
	rc.Send("2.52.52.52.52.52.52.52.52.52.52.52.5===========================================");
	int i=0;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
		rc.PushStreamName("sub2");
		rc.Send("Data1", "Stream1");
		rc.Send("Data1a", "Stream1a");
		rc.PushStreamName("sub1");
		rc.Send("Data1b", "Stream1b");
		rc.Send("Data1b", "@AbsoluteStream");
		rc.PushStreamName("sub2");
		rc.Send("Data2");
		rc.PopStreamName();
		rc.SetThreadName("Main");
		rc.Send("Data3", "Stream3", "sdfsdf");
		rc.PopStreamName();
		Sleep(300);
	}

	rc.Send("3333333333333333333333333333===========================================");
	rc.Disconnect();

	RCP::RCPClient *pRC = RCP::RCPClientsManager::GetInstance().GetRcpClientForCurrentThread();
	pRC->ConnectToServer("tcp://127.0.0.1:55557");
	rc.Send("*************************************************************");
	rc.Send("*************************************************************");
	rc.Send("*************************************************************");
	rc.Send("*************************************************************");
	rc.Send("*************************************************************");
	Sleep(1000);
	i=0;
	pRC->Send("44444444444444444444444444444===========================================");
	pRC->SetStreamPrefix("");
	while(GetAsyncKeyState(VK_ESCAPE) == false)
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
	RCP::RCPClient rc;
	rc.ConnectToServer("tcp://127.0.0.1:55557");
	Sleep(1000);

	int i=0;
	std::vector<int> values;
	std::vector<float> valuesList;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
		i++;
		std::ostringstream stringStream;
		stringStream << "i=" << i;
		rc.Send(stringStream.str().c_str(), "Stream1");
		rc.Send(i, "Stream2");
		rc.Send(i*0.757, "Stream3");
		rc.Send(values);
		rc.Send(valuesList);
		rc.Send(i%3 == 0);
		values.push_back(i*i);
		valuesList.push_back(1.0/i);
		Sleep(1000);
		if(i%100 == 0)
			printf("i=%d\n", i);
	}

	rc.Disconnect();
}

void Test3()
{
	RCConnect("tcp://127.0.0.1:55557");

	int i=0;
	std::vector<int> values;
	std::vector<float> valuesList;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
// 		RCVar(i);
// 		RCVar(values);
// 		RCVar(valuesList);
// 		
 		RCPrint("test1");
// 		RCPrint("test2", "streamA");
// 		RCPrint("test3", "@streamB");

		RCPrintf("formating %d, %f", i*i, 10.0/i);

		i++;
		values.push_back(i*i);
		valuesList.push_back(1.0/i);
		Sleep(500);
		if(i%100 == 0)
			printf("i=%d\n", i);
	}

	RCDisconnect();
}

void Test4()
{
	RCSetServerAddress("tcp://127.0.0.1:55557");
	RCThreadGuard("MainThread");
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
		RCPrint(rand());
		RC->Set("FileName", __FILE__)->Set("CodeLine", S__LINE__)->Set("FunctionSignature", __FUNCSIG__)->Send("test file");
		Sleep(500);
	}
}

BOOL WINAPI CtrlHandler(DWORD dwType)
{
	RCDisconnect();
	return TRUE;
}

int main()
{
	//We need this to close ZMQ connection correctly
	SetConsoleCtrlHandler(CtrlHandler, TRUE);

// 	Test1();
// 	Test2();
// 	Test3();
	Test4();
	return 0;
}

