#ifndef DEFINELOG
#define DEFINELOG

#include "Defines.h"

#if PLATFORM == ESP
    #include "Log.h"
#elif PLATFORM == WIN64
    #include "pcbuild\Log.h"
#endif

#endif
