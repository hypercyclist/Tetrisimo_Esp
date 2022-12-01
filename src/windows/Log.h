#ifndef LOG_H
#define LOG_H

#include <string>

class Log
{
    public:
        Log();
        ~Log();
        static void init();
        static void print(std::string _text, std::string _debugLevel);
        static void println(std::string _text, std::string _debugLevel);
        static void print(int _value, std::string _debugLevel);
        static void println(int _value, std::string _debugLevel);
};

#endif
