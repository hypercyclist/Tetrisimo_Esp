#include "Color.h"

// #include <SoftwareSerial.h>

Color::Color(int _r, int _g, int _b) : r(_r), g(_g), b(_b)
{
    update();
}

Color::~Color()
{
}

Color::Color(uint16_t _color)
{
    color16 = _color;
    // r = (color16 >> 8) & 0xF8;
    // g = (color16 >> 3) & 0xFC;
    // b = (color16 << 3) & 0xF8;
}

Color::Color(const Color& _fromColor)
{
    // color16 = _fromColor.toUint16();
    // r = (color16 >> 8) & 0xF8;
    // g = (color16 >> 3) & 0xFC;
    // b = (color16 << 3) & 0xF8;
}

// void Color::setBrightnessParameters(int* , int)
// {

// }

// uint16_t Color::calculateUint16(int _r, int _g, int _b)
// {
//     // return ((_r / 8) << 11) | ((_g / 4) << 5) | (_b / 8);
//     // return ((_r & 0xF8) << 8) | ((_g & 0xFC) << 3) | (_b >> 3);
//     uint8_t r = _r / (*displayBrightnessLevels) * (*displayBrightness);
//     uint8_t g = _g / (*displayBrightnessLevels) * (*displayBrightness);
//     uint8_t b = _b / (*displayBrightnessLevels) * (*displayBrightness);
//     return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
// }

void Color::update()
{
    color16 = toUint16();
}

uint16_t Color::getUint16() const
{
    return color16;
}

uint16_t Color::toUint16() const
{
    return ((getR() & 0xF8) << 8) | ((getG() & 0xFC) << 3) | (getB() >> 3);
}

void Color::setColorRgb(int _r, int _g, int _b)
{
    r = _r;
    g = _g;
    b = _b;
    update();
}

int Color::getR() const
{
    return r;
}

void Color::setR(int _r)
{
    r = _r;
    update();
}

int Color::getG() const
{
    return g;
}

void Color::setG(int _g)
{
    g = _g;
    update();
}

int Color::getB() const
{
    return b;
}

void Color::setB(int _b)
{
    b = _b;
    update();
}
