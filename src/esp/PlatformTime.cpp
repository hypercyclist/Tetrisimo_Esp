#include "PlatformTime.h"

#include "Arduino.h"
#include "user_interface.h"

PlatformTime::PlatformTime()  { }
PlatformTime::~PlatformTime() { }

void PlatformTime::delayTimeMs(int _timeMs)
{
    delay(20);
}

time_t PlatformTime::getTimeMs()
{
    return time_t(system_get_time() / 1000);
}
