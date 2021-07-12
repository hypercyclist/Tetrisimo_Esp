#include "PlatformTime.h"
#include "user_interface.h"

PlatformTime::PlatformTime() 
{
}

PlatformTime::~PlatformTime()
{
}

void PlatformTime::delay(int _timeMs)
{
    delay(_timeMs);
}

time_t PlatformTime::getTimeMs()
{
    return (time_t)(system_get_time() / 1000);
}
