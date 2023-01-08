#include "Config.h"
#include <algorithm>
#include "Color.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include "IpAddress.h"
#include "Port.h"
#include "ResourceTheme.h"
#include "ServiceAddress.h"
#include "WifiSettings.h"

// [net[1], ghost[1], shake[1], 
//  wifiName[32], wifiPath[64], wifiIp[4], wifiGateway[4], 
//  wifiMask[4], wifiDns1[4], wifiDns2[4], globalServerIp[4], globalPort[1*4], 
//  record[10*4]] - in uint8_t.

// record int[10]

void Config::readConfig()
{
    std::ifstream configFileRead("config.dat", std::ios_base::binary);
    std::vector<uint8_t> byteArray(std::istreambuf_iterator<char>(configFileRead), {});
    configFileRead.close();
    // for (uint8_t value : byteArray) std::cout << (int)value << " ";
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;

    useNetState = uint8FromByteArray(byteArray);
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    useGhostState = uint8FromByteArray(byteArray);
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    useVibrationState = uint8FromByteArray(byteArray);
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setWifiSsid(stringFromByteArray(32, byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setWifiPassword(stringFromByteArray(64, byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setDhcpEnabled(uint8FromByteArray(byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setIpAddress(ipAddressFromByteArray(byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setGatewayAddress(ipAddressFromByteArray(byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setSubnetMask(ipAddressFromByteArray(byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setDns1Address(ipAddressFromByteArray(byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    wifiSettings->setDns2Address(ipAddressFromByteArray(byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    globalServerAddress->setIpAddress(ipAddressFromByteArray(byteArray));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    // for (uint8_t value : byteArray) std::cout << (int)value << " ";
    globalServerAddress->setPort(Port(intFromByteArray(byteArray)));
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;
    displayBrightness = uint8FromByteArray(byteArray);
    playerName = stringFromByteArray(20, byteArray);
    serverName = stringFromByteArray(30, byteArray);
    gameMode = uint8FromByteArray(byteArray);
    serverType = uint8FromByteArray(byteArray);
    customTheme->setUndefinedColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFocusColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setUnfocusColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setBorderColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setBackgroundMenuColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setBackgroundGameColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setNetColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFigureIColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFigureLColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFigureJColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFigureZColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFigureSColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFigureTColor(Color(uint16FromByteArray(byteArray)));
    customTheme->setFigureOColor(Color(uint16FromByteArray(byteArray)));
}

void Config::writeConfig()
{
    std::vector<uint8_t> byteArray;
    uint8ToByteArray(useNetState, byteArray);
    uint8ToByteArray(useGhostState, byteArray);
    uint8ToByteArray(useVibrationState, byteArray);
    stringToByteArray(wifiSettings->getWifiSsid(), 32, byteArray);
    stringToByteArray(wifiSettings->getWifiPassword(), 64, byteArray);
    uint8ToByteArray(wifiSettings->getDhcpEnabled(), byteArray);
    ipAddressToByteArray(wifiSettings->getIpAddress(), byteArray);
    ipAddressToByteArray(wifiSettings->getGatewayAddress(), byteArray);
    ipAddressToByteArray(wifiSettings->getSubnetMask(), byteArray);
    ipAddressToByteArray(wifiSettings->getDns1Address(), byteArray);
    ipAddressToByteArray(wifiSettings->getDns2Address(), byteArray);
    ipAddressToByteArray(globalServerAddress->getIpAddress(), byteArray);
    intToByteArray(globalServerAddress->getPort().getPortAddress(), byteArray);
    uint8ToByteArray(displayBrightness, byteArray);
    stringToByteArray(playerName, 20, byteArray);
    stringToByteArray(serverName, 30, byteArray);
    uint8ToByteArray(gameMode, byteArray);
    uint8ToByteArray(serverType, byteArray);
    uint16ToByteArray(customTheme->getUndefinedColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFocusColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getUnfocusColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getBorderColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getBackgroundMenuColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getBackgroundGameColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getNetColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFigureIColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFigureLColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFigureJColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFigureZColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFigureSColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFigureTColor().toUint16(), byteArray);
    uint16ToByteArray(customTheme->getFigureOColor().toUint16(), byteArray);
    for(int i = 0; i < recordsCount; i++) intToByteArray(records[i], byteArray);
    // std::cout << "Config size: " << byteArray.size() << " bytes." << std::endl;

    // for (uint8_t value : byteArray) std::cout << (int)value << " ";
    std::ofstream configFileWrite("config.dat", std::ios_base::binary);
    std::ostream_iterator<uint8_t> byteIteratorWrite(configFileWrite);
    std::copy(std::begin(byteArray), std::end(byteArray), byteIteratorWrite);
    configFileWrite.close();
}

void Config::stringToByteArray(std::string _string, int _stringWantSize, 
    std::vector<uint8_t>& _byteArray)
{
    _string.resize(_string.size() + (_stringWantSize - _string.size()), '\0');
    for (char letter : _string) uint8ToByteArray(letter, _byteArray);
}

std::string Config::stringFromByteArray(int _stringSize, 
    std::vector<uint8_t>& _byteArray)
{
    std::string result(_byteArray.begin(), _byteArray.begin() + _stringSize);
    _byteArray.erase(_byteArray.begin(), _byteArray.begin() + _stringSize);
    result.erase(std::remove(result.begin(), result.end(), '\0'), result.end());
    // std::cout << result << std::endl;
    return result;
}

void Config::ipAddressToByteArray(IpAddress _ipAddress, 
    std::vector<uint8_t>& _byteArray)
{
    for (int i = 0; i < 4; i++) uint8ToByteArray(_ipAddress.byte[i], _byteArray);
}

IpAddress Config::ipAddressFromByteArray(std::vector<uint8_t>& _byteArray)
{
    IpAddress result(0, 0, 0, 0);
    for (int i = 0; i < 4; i++) 
    { 
        result.byte[i] = uint8FromByteArray(_byteArray);
    }
    return result;
}

void Config::intToByteArray(int _int, std::vector<uint8_t>& _byteArray)
{
    for (int i = 0; i < 4; i++) uint8ToByteArray(_int >> (i * 8), _byteArray);
    // std::cout << _int << std::endl;
}

int Config::intFromByteArray(std::vector<uint8_t>& _byteArray)
{
    unsigned int result = int(
        (uint8_t)(_byteArray[3]) << 24 | (uint8_t)(_byteArray[2]) << 16 |
        (uint8_t)(_byteArray[1]) << 8  | (uint8_t)(_byteArray[0])
    );
    _byteArray.erase(_byteArray.begin(), _byteArray.begin() + 4);
    // std::cout << result << std::endl;
    return result;
}

void Config::uint16ToByteArray(uint16_t _uint16, 
    std::vector<uint8_t>& _byteArray)
{
    uint8ToByteArray(_uint16 >> (8), _byteArray);
    uint8ToByteArray(_uint16 >> (0), _byteArray);
}

uint16_t Config::uint16FromByteArray(std::vector<uint8_t>& _byteArray)
{
    uint16_t result = uint16_t(
        (uint8_t)(_byteArray[0]) << 8  | (uint8_t)(_byteArray[1])
    );
    _byteArray.erase(_byteArray.begin(), _byteArray.begin() + 2);
    return result;
}

void Config::uint8ToByteArray(uint8_t _uint8, std::vector<uint8_t>& _byteArray)
{
    _byteArray.push_back(_uint8);
}

uint8_t Config::uint8FromByteArray(std::vector<uint8_t>& _byteArray)
{
    uint8_t result = _byteArray[0];
    _byteArray.erase(_byteArray.begin());
    return result;
}

// char tempByteArray[byteArray.size()];
// for (int i = 0; i < byteArray.size(); i++) tempByteArray[i] = byteArray[i]; 
// configFileWrite.write(tempByteArray, byteArray.size());
// for (const auto &data : byteArray) configFileWrite << data;

// std::istream_iterator<uint8_t> byteIteratorRead(configFileRead), end;
// std::vector<uint8_t> byteArray2(byteIteratorRead, end);
// for (uint8_t value : byteArray2) std::cout << (int)value << " ";
// char tempByteArray2[byteArray.size()];
// configFileRead.read(tempByteArray2, byteArray.size());
// for (uint8_t value : tempByteArray2) byteArray2.push_back(value);
