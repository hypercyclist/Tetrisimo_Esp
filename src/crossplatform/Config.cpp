#include "Config.h"
#include "Color.h"
#include "IpAddress.h"
#include "Port.h"
#include "Resistor.h"
#include "ResourceTheme.h"
#include "ServiceAddress.h"
#include "Size.h"
#include "WifiSettings.h"

#include <iostream>

Config::Config()
{
    initializeConstants();
    initializeWifiSettings();
    readConfig();
}

Config::~Config()
{

}

void Config::initializeConstants()
{
    displaySize = std::make_unique<Size>(128, 160);
    displayScale = 3;
    int displayMaximumBrightness = 10;
    pinDisplayCS = 4;
    pinDisplayDC = 5;
    pinDisplayRST = 16;
    // pinKeyboardAdc = A0;
    pinKeyboardAdc = 300;
    recordsCount = 15;
    records.resize(recordsCount, 0);
    caveLightsTheme = std::make_unique<ResourceTheme>();
    caveLightsTheme->setUndefinedColor( Color(0, 0, 0) );
    caveLightsTheme->setFocusColor( Color(250, 200, 50) );
    caveLightsTheme->setUnfocusColor( Color(200, 75, 50) );
    caveLightsTheme->setBorderColor( Color(150, 150, 150) );
    caveLightsTheme->setBackgroundMenuColor( Color(50, 50, 50) );
    caveLightsTheme->setBackgroundGameColor( Color(20, 20, 20) );
    caveLightsTheme->setNetColor( Color(40, 40, 40) );
    caveLightsTheme->setFigureIColor( Color(200, 75, 50) );
    caveLightsTheme->setFigureLColor( Color(75, 250, 150) );
    caveLightsTheme->setFigureJColor( Color(250, 200, 50) );
    caveLightsTheme->setFigureZColor( Color(25, 100, 225) );
    caveLightsTheme->setFigureSColor( Color(75, 150, 150) );
    caveLightsTheme->setFigureTColor( Color(200, 200, 50) );
    caveLightsTheme->setFigureOColor( Color(175, 100, 225) );
    
    redQuakeTheme = std::make_unique<ResourceTheme>();
    redQuakeTheme->setFocusColor( Color(150, 25, 50) );
    redQuakeTheme->setUnfocusColor( Color(250, 200, 50) );
    redQuakeTheme->setBorderColor( Color(150, 25, 50) );
    redQuakeTheme->setBackgroundMenuColor( Color(0, 0, 0) );
    redQuakeTheme->setBackgroundGameColor( Color(0, 0, 0) );
    redQuakeTheme->setNetColor( Color(0, 0, 0) );
    redQuakeTheme->setFigureIColor( Color(250, 25, 75) );
    redQuakeTheme->setFigureLColor( Color(25, 250, 125) );
    redQuakeTheme->setFigureJColor( Color(0, 75, 175) );
    redQuakeTheme->setFigureZColor( Color(25, 50, 50) );
    redQuakeTheme->setFigureSColor( Color(250, 250, 75) );
    redQuakeTheme->setFigureTColor( Color(50, 250, 50) );
    redQuakeTheme->setFigureOColor( Color(225, 75, 225) );

    customTheme = std::make_unique<ResourceTheme>();

    IpAddress globalServerIpAddress(127, 0, 0, 1);
    Port globalServerPort(8080);
    globalServerAddress = std::make_unique<ServiceAddress>(
        globalServerIpAddress, globalServerPort);
}

void Config::initializeWifiSettings()
{
    wifiSettings = std::make_unique<WifiSettings>();
}

Size Config::getDisplaySize() { return *displaySize; }
int Config::getDisplayScale() { return displayScale; }
int Config::getPinDisplayCS() { return pinDisplayCS; }
int Config::getPinDisplayDC() { return pinDisplayDC; }
int Config::getPinDisplayRST() { return pinDisplayRST; }
int Config::getDisplayBrightness() { return displayBrightness; }
int Config::getDisplayMaximumBrightness() { return displayMaximumBrightness; }

ResourceTheme Config::getCaveLightsTheme() { return *caveLightsTheme; }
ResourceTheme Config::getRedQuakeTheme() { return *redQuakeTheme; }
ResourceTheme Config::getCustomTheme() { return *customTheme; }

std::string Config::getPlayerName() { return playerName; }
void Config::setPlayerName(std::string _playerName) { playerName = _playerName; }

WifiSettings Config::getWifiSettings() { return *wifiSettings; }
void Config::setWifiSettings(WifiSettings _wifiSettings) {
    wifiSettings = std::make_unique<WifiSettings>(_wifiSettings);
}
ServiceAddress Config::getGlobalServerAddress() { return *globalServerAddress; }
void Config::setGlobalServerAddress(ServiceAddress _globalServerAddress) {
    globalServerAddress = std::make_unique<ServiceAddress>(_globalServerAddress);
}

bool Config::getUseNetState() { return useNetState; }
void Config::setUseNetState(bool _state) { useNetState = _state; }
bool Config::getUseGhostState() { return useGhostState; }
void Config::setUseGhostState(bool _state) { useGhostState = _state; }
bool Config::getUseVibrationState() { return useVibrationState; }
void Config::setUseVibrationState(bool _state) { useVibrationState = _state; }

Resistor Config::getUpButtonResistor() { return *upButtonResistor; }
void Config::setUpButtonResistor(Resistor _upButtonResistor) {
    upButtonResistor = std::make_unique<Resistor>(_upButtonResistor);
}

Resistor Config::getDownButtonResistor() { return *downButtonResistor; }
void Config::setDownButtonResistor(Resistor _downButtonResistor) {
    downButtonResistor = std::make_unique<Resistor>(_downButtonResistor);
}

Resistor Config::getLeftButtonResistor() { return *leftButtonResistor; }
void Config::setLeftButtonResistor(Resistor _leftButtonResistor) {
    leftButtonResistor = std::make_unique<Resistor>(_leftButtonResistor);
}

Resistor Config::getRightButtonResistor() { return *rightButtonResistor; }
void Config::setRightButtonResistor(Resistor _rightButtonResistor) {
    rightButtonResistor = std::make_unique<Resistor>(_rightButtonResistor);
}

Resistor Config::getOkButtonResistor() { return *okButtonResistor; }
void Config::setOkButtonResistor(Resistor _okButtonResistor) {
    okButtonResistor = std::make_unique<Resistor>(_okButtonResistor);
}

Resistor Config::getBackButtonResistor() { return *backButtonResistor; }
void Config::setBackButtonResistor(Resistor _backButtonResistor) {
    backButtonResistor = std::make_unique<Resistor>(_backButtonResistor);
}

int Config::getPinKeyboardAdc() { return pinKeyboardAdc; }
