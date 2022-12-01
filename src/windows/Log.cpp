#include "Log.h"

#include <iostream>

Log::Log()
{
}

Log::~Log()
{
}

void Log::init()
{
}

void Log::print(std::string _text, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        std::cout << _text;
    #endif
}

void Log::println(std::string _text, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        std::cout << _text << std::endl;
    #endif
}

void Log::print(int _value, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        std::cout << _value;
    #endif
}

void Log::println(int _value, std::string _debugLevel)
{
    #if DEBUG == TRUE && DEBUG_LEVEL >= _debugLevel
        std::cout << _value << std::endl;
    #endif
}
