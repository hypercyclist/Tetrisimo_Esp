#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H

#include <time.h>

class PlatformTime
{
    public:
        PlatformTime();
        ~PlatformTime();
        static void delayTimeMs(int _timeMs);
        static time_t getTimeMs();
};

#endif
