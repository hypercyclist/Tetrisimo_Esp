#ifndef DEFINEDISPLAY
#define DEFINEDISPLAY

#include "Defines.h"

#if PLATFORM == ESP
    #include "Display.h"
#endif

#if PLATFORM == WIN64
    #include "pcbuild\Display.h"
#endif

#endif
