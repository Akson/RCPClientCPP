// RCPClientCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RCPClient.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	RCP.ConnectToServer("tcp://127.0.0.1:55557");

	while(true)
	{
 		RCP.Print("Data1", "Stream1");
 		RCP.Print("Data2", "Stream2");
 		RCP.Print("Data3", "Stream3", 0, "Win 1");
		Sleep(1000);
	}
	return 0;
}

