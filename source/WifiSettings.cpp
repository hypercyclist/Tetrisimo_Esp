#include "WifiSettings.h"

#include "DefineNetworking.h"

WifiSettings::WifiSettings()
{
    wifiSsid = "home_wifi";
    wifiPassword = "password";
    isDhcpEnabled = true;
    ipAddress = std::make_unique<IpAddress>( IpAddress(192, 168, 0, 10) );
    gatewayAddress = std::make_unique<IpAddress>( IpAddress(192, 168, 0, 1) );
    subnetMask = std::make_unique<IpAddress>( IpAddress(255, 255, 255, 255) );
    dns1Address = std::make_unique<IpAddress>( IpAddress(8, 8, 8, 8) );
    dns2Address = std::make_unique<IpAddress>( IpAddress(8, 8, 4, 4) );
}

WifiSettings::WifiSettings(WifiSettings& _fromWifiSettings)
{
    wifiSsid = _fromWifiSettings.getWifiSsid();
    wifiPassword = _fromWifiSettings.getWifiPassword();
    isDhcpEnabled = _fromWifiSettings.getDhcpEnabled();
    ipAddress = std::make_unique<IpAddress>( _fromWifiSettings.getIpAddress() );
    gatewayAddress = std::make_unique<IpAddress>( _fromWifiSettings.getGatewayAddress() );
    subnetMask = std::make_unique<IpAddress>( _fromWifiSettings.getSubnetMask() );
    dns1Address = std::make_unique<IpAddress>( _fromWifiSettings.getDns1Address() );
    dns2Address = std::make_unique<IpAddress>( _fromWifiSettings.getDns2Address() );
}

WifiSettings::~WifiSettings()
{
}

void WifiSettings::setWifiSsid(std::string _wifiSsid)
{
    wifiSsid = _wifiSsid;
}

std::string WifiSettings::getWifiSsid()
{
    return wifiSsid;
}

void WifiSettings::setWifiPassword(std::string _wifiPassword)
{
    wifiPassword = _wifiPassword;
}

std::string WifiSettings::getWifiPassword()
{
    return wifiPassword;
}

void WifiSettings::setDhcpEnabled(bool _isDhcpEnabled)
{
    isDhcpEnabled = _isDhcpEnabled;
}

bool WifiSettings::getDhcpEnabled()
{
    return isDhcpEnabled;
}


void WifiSettings::setIpAddress(IpAddress _ipAddress)
{
    ipAddress = std::make_unique<IpAddress>(_ipAddress);
}

IpAddress WifiSettings::getIpAddress()
{
    return *ipAddress;
}

void WifiSettings::setGatewayAddress(IpAddress _gatewayAddress)
{
    gatewayAddress = std::make_unique<IpAddress>(_gatewayAddress);
}

IpAddress WifiSettings::getGatewayAddress()
{
    return *gatewayAddress;
}

void WifiSettings::setSubnetMask(IpAddress _subnetMask)
{
    subnetMask = std::make_unique<IpAddress>(_subnetMask);
}

IpAddress WifiSettings::getSubnetMask()
{
    return *subnetMask;
}

void WifiSettings::setDns1Address(IpAddress _dns1Address)
{
    dns1Address = std::make_unique<IpAddress>(_dns1Address);
}

IpAddress WifiSettings::getDns1Address()
{
    return *dns1Address;
}

void WifiSettings::setDns2Address(IpAddress _dns2Address)
{
    dns2Address = std::make_unique<IpAddress>(_dns2Address);
}

IpAddress WifiSettings::getDns2Address()
{
    return *dns2Address;
}
