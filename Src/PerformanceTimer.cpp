#include "PerformanceTimer.h"
#include "RCP.h"

PerformanceTimer::PerformanceTimer()
{
	PCFreq = 0.0;
	CounterStart = 0;
	Start();
	LastPrintedValue = 0;
}

PerformanceTimer::~PerformanceTimer()
{
}

void PerformanceTimer::Start()
{
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
		throw "QueryPerformanceFrequency failed!";

	PCFreq = double(li.QuadPart)/1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double PerformanceTimer::GetCount()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	return double(li.QuadPart-CounterStart) / PCFreq;
}

double PerformanceTimer::ReStart()
{
	double res;
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	res = double(li.QuadPart-CounterStart) / PCFreq;
	Start();
	LastPrintedValue = res;

	return res;
}

void PerformanceTimer::Print(char* name, bool reset)
{
	double curValue = reset?ReStart():GetCount();
	if (curValue < 1000) RCPrintf("TIMER (%s): %7.3f ms (delta %7.3f ms)\n", name, curValue, curValue-LastPrintedValue);
	else RCPrintf("TIMER (%s): %7.3f s (delta %7.3f ms)\n", name, curValue/1000.0, curValue-LastPrintedValue);

	LastPrintedValue = curValue;
}

void PerformanceTimer::PrintLocal(char* name, bool reset)
{
	double curValue = reset?ReStart():GetCount();
	if (curValue < 1000) printf("TIMER (%s): %7.3f ms (delta %7.3f ms)\n", name, curValue, curValue-LastPrintedValue);
	else printf("TIMER (%s): %7.3f s (delta %7.3f ms)\n", name, curValue/1000.0, curValue-LastPrintedValue);

	LastPrintedValue = curValue;
}
