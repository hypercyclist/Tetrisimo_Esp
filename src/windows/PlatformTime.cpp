#include "PlatformTime.h"

// #include <windows.h>
#include <unistd.h>
#include <time.h>

#include <iostream>

PlatformTime::PlatformTime() { }
PlatformTime::~PlatformTime() { }

void PlatformTime::delayTimeMs(int _timeMs)
{
    // Linux version.
    sleep(_timeMs);
    // Windows version.
    // Sleep(_timeMs);
}

time_t PlatformTime::getTimeMs()
{
    // Windows version.
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000 + now.tv_nsec / 1000000.0;
}

// static time_t s_frequency;
// static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
// if (s_use_qpc) {
//     time_t now;
//     QueryPerformanceCounter(&now);
//     return (1000LL * now.QuadPart) / s_frequency.QuadPart;
// } else {
//     return GetTickCount();
// }
// static LARGE_INTEGER s_frequency;
// static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
// if (s_use_qpc) {
//     LARGE_INTEGER now;
//     QueryPerformanceCounter(&now);
//     return (1000LL * now.QuadPart) / s_frequency.QuadPart;
// } else {
//     return GetTickCount();
// }