#include "IpAddress.h"

IpAddress::IpAddress(unsigned char _byte0, unsigned char _byte1, unsigned char _byte2, unsigned char _byte3) 
{
    byte[0] = _byte0;
    byte[1] = _byte1;
    byte[2] = _byte2;
    byte[3] = _byte3;
}

IpAddress::~IpAddress()
{
}

void IpAddress::setIpAddress(unsigned char _byte0, unsigned char _byte1, unsigned char _byte2, unsigned char _byte3)
{
    byte[0] = _byte0;
    byte[1] = _byte1;
    byte[2] = _byte2;
    byte[3] = _byte3;
}
