#ifndef DEFINETIME
#define DEFINETIME

#include "Defines.h"

#if PLATFORM == ESP
    #include "PlatformTime.h"
#endif

#if PLATFORM == WIN64
    #include "pcbuild/PlatformTime.h"
#endif

#endif
