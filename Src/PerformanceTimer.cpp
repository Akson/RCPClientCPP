#include "PerformanceTimer.h"
#include "RCP.h"
#include <windows.h>

PerformanceTimer::PerformanceTimer(const char *timerFileName/* = ""*/, int timerCodeLine/* = -1*/)
{
    m_PCFreq = 0.0;
    m_CounterStart = 0;
    Start();
    m_LastPrintedValue = 0;
    m_TimerInitializationTime = m_CounterStart;
    m_TimerFileName = timerFileName;
    m_TimerCodeLine = timerCodeLine;
}

PerformanceTimer::~PerformanceTimer()
{
}

inline void PerformanceTimer::Start()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        throw "QueryPerformanceFrequency failed!";

    m_PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    m_CounterStart = li.QuadPart;
}

inline double PerformanceTimer::GetCount()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);

    return double(li.QuadPart - m_CounterStart) / m_PCFreq;
}

inline double PerformanceTimer::ReStart()
{
    double res = GetCount();
    Start();
    return res;
}

void PerformanceTimer::Print(const char *name, bool reset)
{
    double curValue = reset ? ReStart() : GetCount();
    std::string streamName = "[TIMER] ";
    streamName += name;
    if(curValue < 1000) RC.Stream(streamName).Set("ProcessingSequence", "_Text").SendFormated("TIMER (%s): %7.3f ms (delta %7.3f ms)", name, curValue, curValue - m_LastPrintedValue);
    else RC.Stream(streamName).Set("ProcessingSequence", "_Text").SendFormated("TIMER (%s): %7.3f s (delta %7.3f ms)", name, curValue / 1000.0, curValue - m_LastPrintedValue);

    RC.Stream(streamName).
        Set("ProcessingSequence", "_Timer").
        Set("EventName", name).
        Set("TimerInitializationTime", m_TimerInitializationTime).
        Set("TimerFileName", m_TimerFileName).
        Set("TimerCodeLine", m_TimerCodeLine).
        Send(curValue);

    m_LastPrintedValue = curValue;
}

void PerformanceTimer::PrintLocal(const char *name, bool reset)
{
    double curValue = reset ? ReStart() : GetCount();
    if(curValue < 1000) printf("TIMER (%s): %7.3f ms (delta %7.3f ms)\n", name, curValue, curValue - m_LastPrintedValue);
    else printf("TIMER (%s): %7.3f s (delta %7.3f ms)\n", name, curValue / 1000.0, curValue - m_LastPrintedValue);

    m_LastPrintedValue = curValue;
}
