#include "PerformanceTimer.h"
#include "RCP.h"
#include <windows.h>
#include "json\json.h"

PerformanceTimer::PerformanceTimer(const char *timerName/* = ""*/, const char *timerFileName/* = ""*/, int timerCodeLine/* = -1*/)
{
    m_PCFreq = 0.0;
    m_CounterStart = 0;
    Start();
    m_TimerInitializationTime = m_CounterStart;
    m_TimerFileName = timerFileName;
    m_TimerCodeLine = timerCodeLine;
    m_TimerName = timerName;
}

PerformanceTimer::~PerformanceTimer()
{
    Print();
}

void PerformanceTimer::Start()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        throw "QueryPerformanceFrequency failed!";

    m_PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    m_CounterStart = li.QuadPart;
}

double PerformanceTimer::GetCount()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);

    return double(li.QuadPart - m_CounterStart) / m_PCFreq;
}

double PerformanceTimer::ReStart()
{
    m_TickTimes.clear();
    m_TickNames.clear();

    double res = GetCount();
    Start();
    return res;
}

void PerformanceTimer::Tick(const char *eventName)
{
    m_TickTimes.push_back(GetCount());
    m_TickNames.push_back(eventName);
}

void PerformanceTimer::Print()
{
    Json::Value root;
    root["Timer name"] = m_TimerName;
    root["Total time"] = GetCount();
    for(int i = 0; i < m_TickTimes.size(); i++)
    {
        Json::Value tick;
        tick["Name"] = m_TickNames[i];
        tick["Time"] = m_TickTimes[i];
        root["Events"].append(tick);
    }
    
    Json::FastWriter fw;
    std::string jsonStr = fw.write(root);

    std::string streamName = "[TIMER] ";
    streamName += m_TimerName;

    RC.Stream(streamName).
        Set("ProcessingSequence", "_Timer").
        Set("TimerInitializationTime", m_TimerInitializationTime).
        Set("TimerFileName", m_TimerFileName).
        Set("TimerCodeLine", m_TimerCodeLine).
        Set("DataType", "JSON").
        Send(jsonStr.c_str());

    //     if(curValue < 1000) RC.Stream(streamName).Set("ProcessingSequence", "_Text").SendFormated("TIMER (%s): %7.3f ms (delta %7.3f ms)", eventName, curValue, curValue - m_LastPrintedValue);
    //     else RC.Stream(streamName).Set("ProcessingSequence", "_Text").SendFormated("TIMER (%s): %7.3f s (delta %7.3f ms)", eventName, curValue / 1000.0, curValue - m_LastPrintedValue);
}
