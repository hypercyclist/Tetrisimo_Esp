#ifndef STRINGUTF_H

#include <string>

// Russian language support string functions. Russian unicoded symbol take two
// char in string, so length of 2-symbols string is 4-symbols by native length
// function. Static functions override classic functions with same arguments.
class StringUtf
{
    private:
        static std::string russianCharacters;
    public:
        static int length(std::string _string);
        static bool isCharacterRussian(char* _letter);
        static std::string substr(std::string _string, int _startIndex, int _number);
        static std::string substr(std::string _string, int _startIndex);
};

#endif
