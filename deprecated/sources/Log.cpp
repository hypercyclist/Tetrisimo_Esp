#include "Log.h"

#include <SoftwareSerial.h>

Log::Log()
{
}

Log::~Log()
{
}

void Log::init()
{
    Serial.begin(115200);
}

void Log::print(std::string _text, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        Serial.print(_text.c_str());
    #endif
}

void Log::println(std::string _text, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        Serial.println(_text.c_str());
    #endif
}

void Log::print(int _value, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        Serial.print(_value);
    #endif
}

void Log::println(int _value, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        Serial.println(_value);
    #endif
}
