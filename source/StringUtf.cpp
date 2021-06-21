#include "StringUtf.h"
#include <SoftwareSerial.h>

std::string StringUtf::russianCharacters = "абвгдеёжзиклмнопрстуфхцчшщъыьэюя";

int StringUtf::length(std::string _string)
{
    int realLength = 0;
    for (int i = 0; i < _string.length(); i++)
    {
        char letter[2] = {_string[i], _string[i + 1]};
        if (isCharacterRussian(_string, letter))
        {
            i++;
        }
        realLength++;
    }
    return realLength;
}

bool StringUtf::isCharacterRussian(std::string _string, char* _letter)
{
    for(int i = 0; i < russianCharacters.length(); i += 2)
    {
        if (russianCharacters[i] == _letter[0]
            && russianCharacters[i + 1] == _letter[1])
        {
            return true;
        }
    }
}

std::string StringUtf::substr(std::string _string, int _startIndex, int _number)
{
    Serial.println("wrap:");
    Serial.println(_number);
    int realIndex = 0;
    int realStartIndex = 0;
    int realNumber = 0;
    for(int i = 0; i < _string.size(); i++)
    {
        if (realIndex == _startIndex)
        {
            realStartIndex = i;
        }
        if (realIndex == _startIndex + _number)
        {
            realNumber = i - realStartIndex; // Bug is here.
            break;
        }
        char letter[] = {_string[i], _string[i + 1]};
        if (isCharacterRussian(_string, letter))
        {
            i++;
        }
        realIndex++;
    }
    return _string.substr(realStartIndex, realNumber);
}

std::string StringUtf::substr(std::string _string, int _startIndex)
{
    int realIndex = 0;
    int realStartIndex = 0;
    for(int i = 0; i < _string.size(); i++)
    {
        if (realIndex == _startIndex)
        {
            realStartIndex = i;
            break;
        }
        char letter[] = {_string[i], _string[i + 1]};
        if (isCharacterRussian(_string, letter))
        {
            i++;
        }
        realIndex++;
    }
    return _string.substr(realStartIndex);
}