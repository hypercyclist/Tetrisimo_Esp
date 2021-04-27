#include "IpAddress.h"

IpAddress::IpAddress(uint8_t _byte0, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3) : IPAddress(_byte0, _byte1, _byte2, _byte3)
{
    // setIpAddress(_byte0, _byte1, _byte2, _byte3);
}

IpAddress::~IpAddress()
{
}

void IpAddress::setIpAddress(uint8_t _byte0, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3)
{
    static_cast<IPAddress>(*this)[0] = _byte0;
    static_cast<IPAddress>(*this)[1] = _byte1;
    static_cast<IPAddress>(*this)[2] = _byte2;
    static_cast<IPAddress>(*this)[3] = _byte3;
}
