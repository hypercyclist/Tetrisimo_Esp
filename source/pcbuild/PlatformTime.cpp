#include "PlatformTime.h"

#include <windows.h>

PlatformTime::PlatformTime() 
{
}

PlatformTime::~PlatformTime()
{
}

void PlatformTime::delay(int _timeMs)
{
    Sleep(_timeMs);
}

time_t PlatformTime::getTimeMs()
{
    // static time_t s_frequency;
    // static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    // if (s_use_qpc) {
    //     time_t now;
    //     QueryPerformanceCounter(&now);
    //     return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    // } else {
    //     return GetTickCount();
    // }
    static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    } else {
        return GetTickCount();
    }
}
