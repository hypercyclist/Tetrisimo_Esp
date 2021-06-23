#include "ServiceAddress.h"

#include "IpAddress.h"
#include "Port.h"

ServiceAddress::ServiceAddress(IpAddress _ipAddress, Port _port)
    : 
    ipAddress( std::make_unique<IpAddress>(_ipAddress) ),
    port( std::make_unique<Port>(_port) )
{
}

ServiceAddress::ServiceAddress(const ServiceAddress& _fromServiceAdrress)
{
    ipAddress = std::make_unique<IpAddress>(_fromServiceAdrress.getIpAddress());
    port = std::make_unique<Port>(_fromServiceAdrress.getPort());
}

ServiceAddress::~ServiceAddress()
{
}

IpAddress ServiceAddress::getIpAddress() const
{
    return *ipAddress;
}

void ServiceAddress::setIpAddress(IpAddress _ipAddress)
{
    ipAddress = std::make_unique<IpAddress>(_ipAddress);
}

Port ServiceAddress::getPort() const
{
    return *port;
}

void ServiceAddress::setPort(Port _port)
{
    port = std::make_unique<Port>(_port);
}
