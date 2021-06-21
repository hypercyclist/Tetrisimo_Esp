#ifndef STRINGUTF_H

#include <string>

class StringUtf
{
    private:
        static std::string russianCharacters;
    public:
        static int length(std::string _string);
        static bool isCharacterRussian(std::string _string, char* _letter);
        static std::string substr(std::string _string, int _startIndex, int _number);
        static std::string substr(std::string _string, int _startIndex);
};

#endif