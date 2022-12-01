#ifndef SERVICEADDRESS_H
#define SERVICEADDRESS_H

class IpAddress;
class Port;

#include <memory>

// Class describe full service address with IP adress and port. Like a structure.
class ServiceAddress
{
    private:
        std::unique_ptr<IpAddress> ipAddress;
        std::unique_ptr<Port> port;
    public:
        ServiceAddress(IpAddress _ipAddress, Port _port);
        ServiceAddress(const ServiceAddress& _fromServiceAdrress);
        ~ServiceAddress();

        IpAddress getIpAddress() const;
        void setIpAddress(IpAddress IpAddress);
        Port getPort() const;
        void setPort(Port IpAddress);
};

#endif
