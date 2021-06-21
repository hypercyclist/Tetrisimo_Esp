#include "Painter.h"
#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "ResourceTheme.h"
#include <SoftwareSerial.h>
#include "StringUtf.h"

Painter::Painter(int _pinDisplayCS, int _pinDisplayDC, int _pinDisplayRST) 
    : Adafruit_ST7735(_pinDisplayCS, _pinDisplayDC, _pinDisplayRST), 
    pinDisplayCS(_pinDisplayCS),
    pinDisplayDC(_pinDisplayDC),
    pinDisplayRST(_pinDisplayRST),
    drawColor(std::make_unique<Color>(0, 0, 0))
{
    initR(INITR_BLACKTAB);
    setTextWrap(false);
}

Painter::~Painter()
{
}

std::shared_ptr<Painter> Painter::painter;

void Painter::setDefault(std::shared_ptr<Painter> _painter)
{
    painter = _painter;
}

std::shared_ptr<Painter> Painter::getPainter()
{
    return painter;
}

void Painter::background(Color _backgroundColor)
{
    fillScreen( _backgroundColor.getUint16() );
}

void Painter::setDrawColor(Color _drawColor)
{
    drawColor = std::make_unique<Color>(_drawColor);
}

Color Painter::getDrawColor()
{
    return *drawColor;
}

void Painter::setResourceTheme(ResourceTheme _resourceTheme)
{
    currentResourceTheme = std::make_shared<ResourceTheme>(_resourceTheme);
}

std::shared_ptr<ResourceTheme> Painter::getResourceTheme()
{
    return currentResourceTheme;
}

void Painter::drawText(std::string _text, Point _positionPoint)
{
    setTextColor( drawColor->getUint16() );
    setCursor( _positionPoint.getX(), _positionPoint.getY() );
    print( fromCyrilic(_text).c_str() );
    // Maybe we can do only print( _text.c_str() ); if text only English. 
}

std::string Painter::fromCyrilic(std::string _cytilicString)
{
    int i;
    int k;
    std::string target;
    unsigned char n;
    char m[2] = { '0', '\0' };

    k = _cytilicString.length();
    i = 0;

    while (i < k) {
    n = _cytilicString[i]; i++;

    if (n >= 0xC0) {
        switch (n) {
        case 0xD0: {
            n = _cytilicString[i]; i++;
            if (n == 0x81) { n = 0xA8; break; }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x2F;
            break;
        }
        case 0xD1: {
            n = _cytilicString[i]; i++;
            if (n == 0x91) { n = 0xB8; break; }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x6F;
            break;
        }
        }
    }
    m[0] = n; 
    target = target + std::string(m);
    }
    return target;
}

void Painter::drawLine(Point _pointA, Point _pointB)
{
    Adafruit_ST7735::drawLine( 
        _pointA.getX(), 
        _pointA.getY(), 
        _pointB.getX(), 
        _pointB.getY(), 
        drawColor->getUint16()
    );
}

void Painter::drawLine(int _x1, int _y1, int _x2, int _y2)
{
    Adafruit_ST7735::drawLine( 
        _x1, 
        _y1, 
        _x2, 
        _y2, 
        drawColor->getUint16()
    );
}

void Painter::drawLine(Point _pointA, Point _pointB, int _lineWidth)
{
    int offsetX;
    int offsetY;
    if( _pointA.getY() == _pointB.getY() )
    {
        offsetX = 0;
        offsetY = 1;
    }
    // else if( _pointA.getY() == _pointB.getY() )
    else
    {
        offsetX = 1;
        offsetY = 0;
    }
    for(int i = 0; i < _lineWidth; i++)
    {
        drawLine( 
            Point( 
                _pointA.getX() + (i * offsetX), 
                _pointA.getY() + (i * offsetY) ), 
            Point( 
                _pointB.getX() + (i * offsetX), 
                _pointB.getY() + (i * offsetY) ) 
        );
    }
}

// Non-painter functions, but i don't know how to attach it to std::string.
int Painter::countWrapSize(int _textSize, int _widgetWidth)
{
    return ( _widgetWidth / (_textSize * 5 + _textSize) ) - 1;
}

Size Painter::countTextSize(std::string _text, int _textSize)
{
    int realLength = StringUtf::length(_text);
    // Every character takes (5x7px * textSize) 
    // + spacing between characters which takes (textSize px).
    Size textSize;
    textSize.setWidth(
        (5 * _textSize * realLength) + ((realLength - 1) * _textSize)
    );
    textSize.setHeight( 7 * _textSize );
    return textSize;
}