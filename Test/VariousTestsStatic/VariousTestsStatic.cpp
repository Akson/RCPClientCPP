#include "RCP.h"
#include <array>
#include <algorithm>
#include <thread>
#include <chrono>
#include <Windows.h>

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
		RC.Stream("@MatrixPrinter/#4x4f").SendBinary(m1.data(), (m1.end() - m1.begin())* sizeof(float));
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

void PrintFunctions()
{
	PerformanceTimer pt;
	int messagesCounter = 0;
	while(GetAsyncKeyState(VK_ESCAPE) == false)
	{
        const char *jsonStr = "{\"glossary\": {\"title\": \"example glossary\",\"GlossDiv\" : {\"title\": \"S\",\"GlossList\" : {\"GlossEntry\": {\"ID\": \"SGML\",\"SortAs\" : \"SGML\",\"GlossTerm\" : \"Standard Generalized Markup Language\",\"Acronym\" : \"SGML\",\"Abbrev\" : \"ISO 8879:1986\",\"GlossDef\" : {\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",\"GlossSeeAlso\" : [\"GML\", \"XML\"]},\"GlossSee\" : \"markup\"}}}}}";


		RCPrinth("<hr>");
		RCPrintf("Just formatted text with a number %d (printf style)", rand());
		RCPrinth("<font size=\"10\" color=\"red\">Html text with custom font!</font>");

        RCPrintj(jsonStr);

        std::vector<int> v(rand()%10);
        for(auto &element : v)
            element = rand();
        RCVar(v);
        RC.Send(v);

		RCVar(rand());

		std::array<float, 4 * 4> matrix;
		std::generate(matrix.begin(), matrix.end(), rand);
		RC.Set("ProcessingSequence", "_2dMatrixTable").Set("MatrixDescription", "#4x4f").SendBinary(matrix.data(), (matrix.end() - matrix.begin())* sizeof(float));
		RC.Set("ProcessingSequence", "_2dMatrixTable").Set("VariableName", "name 123").Set("BinaryDataFormat", "f").Set("Dimensions", "4x4").SendBinary(matrix.data(), (matrix.end() - matrix.begin())* sizeof(float));
		RC.Set("VariableName", "name 123").Set("BinaryDataFormat", "f").Set("Dimensions", "4x4").SendBinary(matrix.data(), (matrix.end() - matrix.begin())* sizeof(float));

		std::array<float, 4 * 4> m1;
		std::generate(m1.begin(), m1.end(), rand);
		RC.Set("ProcessingSequence", "MatrixPrinter/#4x4f").SendBinary(m1.data(), (m1.end() - m1.begin())* sizeof(float));

		RC.Stream("TestStream").Set("ProcessingSequence", "_Text").Send("Test to stream 'TestStream'");
		RC.Set("ProcessingSequence", "_Text").Send("Just text");
		RC.Send(1);
		RC.Send(2.1);
		RC.Send(true);
		RC.Send("Just string");


		printf("%d\n", messagesCounter++);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if(messagesCounter > 5) return;
	}
}

void TimerTest()
{
    int i = 0;
    //while(GetAsyncKeyState(VK_ESCAPE) == false)
    {
        RCPrinth("<br>");
        RCP_TIMER(pt, "Test timer"); 
        std::chrono::milliseconds dura1(200);
        std::this_thread::sleep_for(dura1);
        pt.Tick("Sleep 1 - 200ms");
        std::chrono::milliseconds dura2(500);
        std::this_thread::sleep_for(dura2);
        pt.Tick("Sleep 2 - 500ms");
        std::chrono::milliseconds dura3(300);
        std::this_thread::sleep_for(dura3);
        pt.Tick("Sleep 3 - 300ms");
        printf("Done %d\n", i++);
    }
}

int main()
{
	//We need this to close ZMQ connection correctly
	SetConsoleCtrlHandler(CtrlHandler, TRUE);

	RCSetServerAddress("tcp://localhost:55557");
	RCThreadGuard("MainThread");

	//MatrixPrint();
	//Streams();
	//PrintFunctions();
    TimerTest();

	return 0;
}

