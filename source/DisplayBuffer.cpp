#include "DisplayBuffer.h"
#include "Color.h"
#include <iostream>
#include <SoftwareSerial.h>

const char DisplayBuffer::colorCodes[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
std::map<uint16_t, char> DisplayBuffer::bindedCodes;
std::map<char, uint16_t> DisplayBuffer::bindedColors;

DisplayBuffer::DisplayBuffer(int _buffer)
{
    buffer = new char[_buffer];
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
        buffer[i] = 0x000000;
    }
}

void DisplayBuffer::bindColor(uint16_t _color, char _colorCode)
{
    bindedCodes.insert(std::make_pair(_color, _colorCode));
    bindedColors.insert(std::make_pair(_colorCode, _color));
}

void DisplayBuffer::setColor(int _index, uint16_t _color)
{
    if (bindedCodes.find(_color) == bindedCodes.end()) {
        setColor(_index, Color(0, 0, 0).toUint16());
    }
    bool part = _index % 2;
    if (!part) {
        setLowerBits(&buffer[_index / 2], &bindedCodes[_color]);
    }
    else {
        setUpperBits(&buffer[_index / 2], &bindedCodes[_color]);
    }
}

uint16_t DisplayBuffer::getColor(int _index)
{
    std::map<char, uint16_t>::iterator result;
    bool part = _index % 2;
    if (!part) {
        // Serial.print("l");
        result = bindedColors.find(getLowerBits(&buffer[_index / 2]));
    }
    else {
        // Serial.print("u");
        result = bindedColors.find(getUpperBits(&buffer[_index / 2]));
    }
    if (result == bindedColors.end()) {
        if (_index == 1 * 1 * 128)
        {
            Serial.print("f");
            if (!part) {
                char res = getLowerBits(&buffer[_index / 2]);
                printBits(res);
            }
            else {
                char res = getUpperBits(&buffer[_index / 2]);
                printBits(res);
            }
            Serial.println(Color(0, 0, 0).toUint16());
        }
        return Color(0, 0, 0).toUint16();
    }
    return result->second;
}

char DisplayBuffer::getLowerBits(char* _byte) {
    char result = 0x000000;
    for (int i = 0; i < 4; i++) {
        if ( *_byte & (1 << i) ) { result |= 1 << i; }
    }
    return result;
}

char DisplayBuffer::getUpperBits(char* _byte) {
    char result = 0x000000;
    for (int i = 4; i < 8; i++) {
        if ( *_byte & (1 << (i)) ) { result |= 1 << i - 4; }
    }
    return result;
}

void DisplayBuffer::setLowerBits(char* _byte, char* _colorCode) {
    for (int i = 0; i < 4; i++) {
        if ( *_colorCode & (1 << i) ) { *_byte |= 1 << i; }
    }
}

void DisplayBuffer::setUpperBits(char* _byte, char* _colorCode) {
    for (int i = 4; i < 8; i++) {
        if ( *_colorCode & (1 << (i - 4)) ) { *_byte |= 1 << i; }
    }
}

void DisplayBuffer::printBits(char& _byte)
{
    for (int i = 7; i >= 0; i--) {
        bool bit = _byte & (1 << i);
        Serial.print(bit);
        // std::cout << bit;
    }
    Serial.println();
    // std::cout << std::endl;
}
