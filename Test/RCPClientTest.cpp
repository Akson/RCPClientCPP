#include "RCP.h"
#include <Windows.h>
#include "PerformanceTimer.h"

BOOL WINAPI CtrlHandler(DWORD dwType)
{
	RCDisconnect();
	return TRUE;
}

int main()
{
	//We need this to close ZMQ connection correctly
	SetConsoleCtrlHandler(CtrlHandler, TRUE);

	RCSetServerAddress("tcp://127.0.0.1:55557");
	RCThreadGuard("MainThread");

	PerformanceTimer pt;

	int messagesCounter = 0;
	int totalMessagesCounter = 0;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
		RCVar(totalMessagesCounter++);
		messagesCounter++;
		if(messagesCounter == 10000)
		{
			auto totalTimeS = pt.ReStart() / 1000.0;
			auto timePerMessage = totalTimeS / messagesCounter;
			printf("messagesCounter = %d, totalTime = %fs, timePerMessage = %fms, messagesPerSecond = %d\n", messagesCounter, totalTimeS, timePerMessage * 1000, (int)(1.0 / timePerMessage));
			messagesCounter = 0;
		}
	}

	return 0;
}

