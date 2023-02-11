#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <stdint.h>

// Structure for TCP IP address.
struct IpAddress
{
    uint8_t byte[4];
    IpAddress(uint8_t _byte0, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3);
};

#endif
