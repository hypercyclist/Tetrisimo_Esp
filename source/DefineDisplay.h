#ifndef DEFINEDISPLAY
#define DEFINEDISPLAY

#include "Defines.h"

#if PLATFORM == ESP
    #include "Display.h"
#elif PLATFORM == WIN64
    #include "pcbuild\Display.h"
#endif

#endif
