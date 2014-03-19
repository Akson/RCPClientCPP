#pragma once

#include "RCPExport.h"
#include <stdint.h>

///Just a simple timer class. It starts at the creating moment and stores the last time value inside.
class RCPCLIENT_API PerformanceTimer
{
public:
    static PerformanceTimer &Instance()
    {
        static PerformanceTimer pt;
        return pt;
    }
    PerformanceTimer(const char *timerFileName = "", int timerCodeLine = -1);
    ~PerformanceTimer();

    //Restarts a timer and returns number of ms since start or last restart
    double ReStart();

    //Returns number of ms since start or last restart
    double GetCount();

    //Prints to RCP
    void Print(const char *name, bool reset = false);

    //Print to local console
    void PrintLocal(const char *name, bool reset = false);

private:
    void Start();
    int64_t m_CounterStart;
    double m_PCFreq;
    double m_LastPrintedValue;
    float m_TimerInitializationTime;
    const char *m_TimerFileName;
    int m_TimerCodeLine;
};
