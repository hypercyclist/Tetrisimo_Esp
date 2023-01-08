#include "IpAddress.h"

IpAddress::IpAddress(uint8_t _byte0, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3) 
{
    byte[0] = _byte0;
    byte[1] = _byte1;
    byte[2] = _byte2;
    byte[3] = _byte3;
}
