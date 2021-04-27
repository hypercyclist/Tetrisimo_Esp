#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <ESP8266WiFi.h>

class IpAddress : public IPAddress
{
    private:
    public:
        IpAddress(uint8_t _byte0, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3);
        ~IpAddress();
        void setIpAddress(uint8_t _byte0, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3);
};

#endif