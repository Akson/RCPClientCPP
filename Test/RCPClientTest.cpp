// RCPClientCPP.cpp : Defines the entry point for the console application.
//

#include "RCPClient.h"
#include <Windows.h>

int main()
{
	RCPClient RCP;
	RCP.ConnectToServer("tcp://127.0.0.1:55557");

	while(true)
	{
		RCP.SendMessageToCurrentStream("Data1", "Stream1");
		RCP.SendMessageToCurrentStream("Data1a", "Stream1a");
		RCP.SendMessageToCurrentStream("Data1b", "Stream1b");
		RCP.SendMessageToCurrentStream("Data2", "Stream2");
		RCP.SetThreadName("Main");
		RCP.SendMessageToCurrentStream("Data3", "Stream3", "sdfsdf", "Win 1", 5);
		Sleep(1000);
	}
	
	return 0;
}

