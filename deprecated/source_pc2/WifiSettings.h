#ifndef WIFISETTINGS_H
#define WIFISETTINGS_H

class IpAddress;

#include <memory>
#include <string>

// This class contain WiFi settings for the game.
class WifiSettings
{
    private:
        std::string wifiSsid;
        std::string wifiPassword;
        bool isDhcpEnabled;
        std::unique_ptr<IpAddress> ipAddress;
        std::unique_ptr<IpAddress> gatewayAddress;
        std::unique_ptr<IpAddress> subnetMask;
        std::unique_ptr<IpAddress> dns1Address;
        std::unique_ptr<IpAddress> dns2Address;

    public:
        WifiSettings();
        WifiSettings(WifiSettings& _fromWifiSettings);
        ~WifiSettings();

        void setWifiSsid(std::string _wifiSsid);
        std::string getWifiSsid();

        void setWifiPassword(std::string _wifiPassword);
        std::string getWifiPassword();

        void setDhcpEnabled(bool _isDhcpEnabled);
        bool getDhcpEnabled();

        void setIpAddress(IpAddress _ipAddress);
        IpAddress getIpAddress();

        void setGatewayAddress(IpAddress _gatewayAddress);
        IpAddress getGatewayAddress();

        void setSubnetMask(IpAddress _subnetMask);
        IpAddress getSubnetMask();

        void setDns1Address(IpAddress _dns1Address);
        IpAddress getDns1Address();

        void setDns2Address(IpAddress _dns2Address);
        IpAddress getDns2Address();
};

#endif
