#ifndef DEFINEPAINTER
#define DEFINEPAINTER

#include "Defines.h"

#if PLATFORM == ESP
    #include "Painter.h"
#elif PLATFORM == WIN64
    #include "pcbuild\Painter.h"
#endif

#endif
