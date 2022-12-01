#ifndef DEFINENETWORKING
#define DEFINENETWORKING

#include "Defines.h"

#if PLATFORM == ESP
    #include "IpAddress.h"
#endif

#if PLATFORM == WIN64
    #include "pcbuild\IpAddress.h"
#endif

#endif
