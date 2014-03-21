#pragma once

#include "RCPExport.h"
#include <stdint.h>
#include <vector>
#include <string>

///Just a simple timer class. It starts at the creating moment and stores the last time value inside.
class RCPCLIENT_API PerformanceTimer
{
public:
    PerformanceTimer(const char *timerName = "", const char *timerFileName = "", int timerCodeLine = -1);
    ~PerformanceTimer();

    //Restarts a timer and returns number of ms since start or last restart
    double ReStart();

    //Returns number of ms since start or last restart
    double GetCount();

    //Record event time
    void Tick(const char *eventName);

    //Send results to server and print timer data
    void Print();

private:
    void Start();
    int64_t m_CounterStart;
    double m_PCFreq;
    float m_TimerInitializationTime;
    const char *m_TimerFileName;
    int m_TimerCodeLine;
    const char *m_TimerName;
    std::vector<double> m_TickTimes;
    std::vector<std::string> m_TickNames;
};
