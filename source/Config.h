#ifndef CONFIG_H
#define CONFIG_H

class Color;
class Resistor;
class ResourceTheme;
class Size;
class ServiceAddress;
class WifiSettings;

#include <memory>
#include <string>

// Class describe game config. Config values load values from EEPROM if it's
// changeable values, or initialize from hardcode. Nextly values will be pushed 
// to the objects.
class Config
{
    private:
        std::unique_ptr<Size> displaySize;
        int displayBrightness;
        int displayMaximumBrightness;
        int pinDisplayCS;
        int pinDisplayDC;
        int pinDisplayRST;
        // Pre-made themes and one custom.
        std::unique_ptr<ResourceTheme> caveLightsTheme;
        std::unique_ptr<ResourceTheme> redQuakeTheme;
        std::unique_ptr<ResourceTheme> customTheme;
        std::string playerName;
        std::unique_ptr<WifiSettings> wifiSettings;
        std::unique_ptr<ServiceAddress> globalServerAddress;
        // As long I will use in my physical buttons resistors it will need to
        // count and store their voltage to compare with ADC values.
        std::unique_ptr<Resistor> upButtonResistor;
        std::unique_ptr<Resistor> downButtonResistor;
        std::unique_ptr<Resistor> leftButtonResistor;
        std::unique_ptr<Resistor> rightButtonResistor;
        std::unique_ptr<Resistor> okButtonResistor;
        std::unique_ptr<Resistor> backButtonResistor;
        // ADC pin on processor.
        int pinKeyboardAdc;
        
    public:
        Config();
        ~Config();
        void initializeConstants();
        void readConfig();
        void writeConfig();

        Size getDisplaySize();
        int getPinDisplayCS();
        int getPinDisplayDC();
        int getPinDisplayRST();
        int getDisplayBrightness();
        void setDisplayBrightness(int _displayBrightness);
        int getDisplayMaximumBrightness();

        ResourceTheme getCaveLightsTheme();
        ResourceTheme getRedQuakeTheme();
        ResourceTheme getCustomTheme();

        std::string getPlayerName();
        void setPlayerName(std::string _playerName);
        WifiSettings getWifiSettings();
        void setWifiSettings(WifiSettings _wifiSettings);
        ServiceAddress getGlobalServerAddress();
        void setGlobalServerAddress(ServiceAddress _globalServerAddress);
        
        Resistor getUpButtonResistor();
        void setUpButtonResistor(Resistor _upButtonResistor);
        Resistor getDownButtonResistor();
        void setDownButtonResistor(Resistor _downButtonResistor);
        Resistor getLeftButtonResistor();
        void setLeftButtonResistor(Resistor _leftButtonResistor);
        Resistor getRightButtonResistor();
        void setRightButtonResistor(Resistor _rightButtonResistor);
        Resistor getOkButtonResistor();
        void setOkButtonResistor(Resistor _okButtonResistor);
        Resistor getBackButtonResistor();
        void setBackButtonResistor(Resistor _backButtonResistor);
        int getPinKeyboardAdc();
};

#endif
