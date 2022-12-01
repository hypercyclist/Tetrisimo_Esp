#ifndef IPADDRESS_H
#define IPADDRESS_H

// Class for TCP IP address. Like a structure.
class IpAddress
{
    private:
        unsigned char byte[4];
    public:
        IpAddress(unsigned char _byte0, unsigned char _byte1, unsigned char _byte2, unsigned char _byte3);
        ~IpAddress();
        void setIpAddress(unsigned char _byte0, unsigned char _byte1, unsigned char _byte2, unsigned char _byte3);
};

#endif
