#include "Port.h"

Port::Port(int _portAddress) : portAddress(_portAddress)
{
}

Port::~Port()
{
}

int Port::getPortAddress()
{
    return portAddress;
}

void Port::setPortAddress(int _portAddress)
{
    portAddress = _portAddress;
}
