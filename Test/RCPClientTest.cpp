// RCClientCPP.cpp : Defines the entry point for the console application.
//
#define RCP_STATIC
#include "RCP.h"
#include <Windows.h>
#include <sstream>
#include "PerformanceTimer.h"
#include <vector>



void Test4()
{
	RCSetServerAddress("tcp://127.0.0.1:55557");
	RCThreadGuard("MainThread");

	PerformanceTimer pt;

	int messagesCounter = 0;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
//		RC.Stream("Stream1").Send(rand());
// 		RC.Stream("Stream2").Send("adsfasdf");
// 		RCP::RCPClientsManager::GetRcpClientForCurrentThread().Send("adsfasdf");
// 		RC.SendFormated("s %s d %d f %f", "STRING", rand(), 1.0/rand());
// 
 		RCVar(rand());
		std::vector<int> v;
		v.push_back(3);
		v.push_back(5);
// 		RC.Stream("vector").Send(v);
// 
// 		RC.Stream("bool").Send(true);


		//Sleep(5);

		messagesCounter++;
		if(messagesCounter == 10000)
		{
			auto totalTimeS = pt.ReStart() / 1000.0;
			auto timePerMessage = totalTimeS / messagesCounter;
			printf("messagesCounter = %d, totalTime = %fs, timePerMessage = %fms, messagesPerSecond = %d\n", messagesCounter, totalTimeS, timePerMessage*1000, (int)(1.0/timePerMessage));

			messagesCounter = 0;
		}
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

