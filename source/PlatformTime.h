#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H

#include <time.h>

class PlatformTime
{
    private:
    public:
        PlatformTime();
        ~PlatformTime();

        static void delay(int _timeMs);
        static time_t getTimeMs();
};

#endif
