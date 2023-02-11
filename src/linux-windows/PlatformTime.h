#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H

#include <time.h>

class PlatformTime
{
    private:
        static time_t deltaTimeMs;
    public:
        PlatformTime();
        ~PlatformTime();
        // Sleep for few ms.
        static void sleepTimeMs(int _timeMs);
        // Get world time ms.
        static time_t getTimeMs();
        // Update time from last frame.
        static void updateTime();
        // Get time from last frame.
        static time_t getDeltaTimeMs();
};

#endif
