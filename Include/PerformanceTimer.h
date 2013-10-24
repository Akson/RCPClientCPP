#ifndef _PERFORMANCE_TIMER_H_
#define _PERFORMANCE_TIMER_H_

#include <windows.h>

///Just a simple timer class. It starts at the creating momen and stores the last time value inside.
class PerformanceTimer
{
public:
	PerformanceTimer();
	~PerformanceTimer();

	void Start();
	double ReStart();
	double GetCount();
	void Print(char * name, bool reset = false);
	void PrintLocal(char * name, bool reset = false);

private:
	double PCFreq;
	__int64 CounterStart;
	double LastPrintedValue;

};

#endif
