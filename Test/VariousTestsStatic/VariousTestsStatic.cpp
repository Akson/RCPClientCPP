#include "RCP.h"
#include <Windows.h>
#include "PerformanceTimer.h"
#include <array>
#include <algorithm>
#include <thread>
#include <chrono>

BOOL WINAPI CtrlHandler(DWORD dwType)
{
	RCDisconnect();
	return TRUE;
}

void MatrixPrint()
{
	PerformanceTimer pt;
	int messagesCounter = 0;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
		std::array<float, 4 * 4> matrix;
		std::generate(matrix.begin(), matrix.end(), rand);
		RC.Stream("@MatrixPrinter").Set("BinaryDataFormat", "f").Set("Dimensions", "4x4").SendBinary(matrix.data(), (matrix.end() - matrix.begin())* sizeof(float));
		for each (auto var in matrix)
			printf("%f ", var);

		std::array<float, 4 * 4> m1;
		std::generate(m1.begin(), m1.end(), rand);
		RC.Stream("@MatrixPrinter/4x4f").SendBinary(m1.data(), (m1.end() - m1.begin())* sizeof(float));
		for each (auto var in m1)
			printf("%f ", var);

		std::array<float, 4 * 4> m2;
		std::generate(m2.begin(), m2.end(), rand);
		RC.Set("BinaryDataFormat", "f").Set("Dimensions", "4x4").SendBinary(m2.data(), (m2.end() - m2.begin())* sizeof(float));
		for each (auto var in m2)
			printf("%f ", var);

		std::array<int, 4 * 4> matrixInt;
		std::generate(matrixInt.begin(), matrixInt.end(), rand);
		RC.Stream("@MatrixPrinter").Set("BinaryDataFormat", "i").SendBinary(matrixInt.data(), (matrixInt.end() - matrixInt.begin())* sizeof(int));
		for each (auto var in matrixInt)
			printf("%d ", var);

		RCPrintf("<hr>");

		printf("%d\n", messagesCounter++);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void Streams()
{
	PerformanceTimer pt;
	int messagesCounter = 0;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
		RC.Stream("@MatrixPrinter").SendFormated("test %d", messagesCounter);
		RC.SendFormated("test %d", messagesCounter);
		RC.Stream("Stream1").SendFormated("test %d", messagesCounter);
		RC.Stream("StreamA/StreamB").SendFormated("test %d", messagesCounter);
		RC.Stream("XXXXX").SendFormated("test %d", messagesCounter);

		printf("%d\n", messagesCounter++);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main()
{
	//We need this to close ZMQ connection correctly
	SetConsoleCtrlHandler(CtrlHandler, TRUE);

	RCSetServerAddress("tcp://127.0.0.1:55557");
	RCThreadGuard("MainThread");

	MatrixPrint();
	//Streams();

	return 0;
}

