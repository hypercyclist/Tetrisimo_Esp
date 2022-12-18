#include "DisplayBuffer.h"
#include "Color.h"
#include <iostream>
#include <SoftwareSerial.h>

const char DisplayBuffer::colorCodes[16] = { 
    char(0), char(1), char(2), char(3), char(4), char(5), char(6), char(7),
    char(8), char(9), char(10), char(11), char(12), char(13), char(14), char(15)
};
std::map<uint16_t, char> DisplayBuffer::bindedCodes;
std::map<char, uint16_t> DisplayBuffer::bindedColors;

DisplayBuffer::DisplayBuffer(int _bufferSize)
    : bufferSize(_bufferSize)
{
    buffer = new char[_bufferSize];
    clearBuffer();
}

DisplayBuffer::~DisplayBuffer()
{
    delete[] buffer;
}

void DisplayBuffer::clearBuffer()
{
    for (int i = 0; i < bufferSize; i++)
    {
        buffer[i] = 0;
    }
}

void DisplayBuffer::bindColor(uint16_t _color, char _colorCode)
{
    bindedCodes.insert_or_assign(_color, _colorCode);
    bindedColors.insert_or_assign(_colorCode, _color);
}

void DisplayBuffer::setColor(int _index, uint16_t _color)
{
    // Color()
    if (bindedCodes.find(_color) == bindedCodes.end()) {
        setColor(_index, Color(0, 0, 0).toUint16());
    }
    bool part = _index % 2;
    if (!part) {
        setLowerBits(buffer[_index / 2], bindedCodes[_color]);
    }
    else {
        setUpperBits(buffer[_index / 2], bindedCodes[_color]);
    }
}

uint16_t DisplayBuffer::getColor(int _index)
{
    std::map<char, uint16_t>::iterator result;
    bool part = _index % 2;
    if (!part) {
        // Serial.print("l");
        result = bindedColors.find(getLowerBits(buffer[_index / 2]));
    }
    else {
        // Serial.print("u");
        result = bindedColors.find(getUpperBits(buffer[_index / 2]));
    }
    // char a = buffer[_index / 2];
    // printBits(a);
    // std::cout << int(result->first);
    if (result == bindedColors.end()) {
        // if (!part) {
        //     std::cout << int(getLowerBits(buffer[_index / 2])) << std::endl;
        // }
        // else {
        //     std::cout << int(getUpperBits(buffer[_index / 2])) << std::endl;
        // }


        // if (_index == 1 * 1 * 128)
        // {
        //     Serial.print("f");
        //     if (!part) {
        //         char res = getLowerBits(&buffer[_index / 2]);
        //         printBits(res);
        //     }
        //     else {
        //         char res = getUpperBits(&buffer[_index / 2]);
        //         printBits(res);
        //     }
        //     Serial.println(Color(0, 0, 0).toUint16());
        // }
        return Color(0, 0, 0).toUint16();
    }
    return result->second;
}

char DisplayBuffer::getLowerBits(char& _byte) {
    char result = 0;
    for (int i = 0; i < 4; i++) {
        if ( _byte & (1 << i) ) { result |= 1 << i; }
        else { result &= ~(1 << i); } // Можно не устанавливать.
    }
    return result;
}

char DisplayBuffer::getUpperBits(char& _byte) {
    char result = 0;
    for (int i = 4; i < 8; i++) {
        if ( _byte & (1 << i) ) { result |= 1 << (i - 4); }
        else { result &= ~(1 << (i - 4)); } // Можно не устанавливать.
    }
    return result;
}

void DisplayBuffer::setLowerBits(char& _byte, char& _colorCode) {
    for (int i = 0; i < 4; i++) {
        if ( _colorCode & (1 << i) ) { _byte |= 1 << i; }
        else { _byte &= ~(1 << i); }
    }
}

void DisplayBuffer::setUpperBits(char& _byte, char& _colorCode) {
    for (int i = 4; i < 8; i++) {
        if ( _colorCode & (1 << (i - 4)) ) { _byte |= 1 << i;}
        else { _byte &= ~(1 << i);}
    }
}

void DisplayBuffer::printBits(char& _byte)
{
    for (int i = 7; i >= 0; i--) {
        bool bit = _byte & (1 << i);
        // Serial.print(bit);
        std::cout << bit;
    }
    // Serial.println();
    // std::cout << std::endl;
}

void DisplayBuffer::test(uint16_t _color)
{
    for (int i = 0; i < 5; i++) {
        printBits(buffer[i]); std::cout << " ";
    }
}
