#include "Painter.h"
#include "Color.h"
#include "DisplayBuffer.h"
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
    drawColor(std::make_unique<Color>(0, 0, 0)),
    oldBuffer(std::make_shared<DisplayBuffer>(bufferSize)),
    buffer(std::make_shared<DisplayBuffer>(bufferSize)),
    diffBuffer(std::make_shared<DisplayBuffer>(bufferSize))
{
    initR(INITR_BLACKTAB);
    setTextWrap(false);
}

Painter::~Painter()
{
}

void Painter::startWrite(void) { }
void Painter::endWrite(void) { }

void Painter::startWriteReal(void) {
  SPI_BEGIN_TRANSACTION();
  if (_cs >= 0)
    SPI_CS_LOW();
}

void Painter::endWriteReal(void) {
  if (_cs >= 0)
    SPI_CS_HIGH();
  SPI_END_TRANSACTION();
}

void Painter::writePixel(int16_t _x, int16_t _y, uint16_t _color) 
{
    if ((_x >= 0) && (_x < _width) && (_y >= 0) && (_y < _height)) 
    {
        buffer->setColor(_x + _y * ST7735_TFTWIDTH_128, _color);
    }
}

void Painter::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                    uint16_t _color) {
  if (w && h) {   // Nonzero width and height?
    if (w < 0) {  // If negative width...
      x += w + 1; //   Move X to left edge
      w = -w;     //   Use positive width
    }
    if (x < _width) { // Not off right
      if (h < 0) {    // If negative height...
        y += h + 1;   //   Move Y to top edge
        h = -h;       //   Use positive height
      }
      if (y < _height) { // Not off bottom
        int16_t x2 = x + w - 1;
        if (x2 >= 0) { // Not off left
          int16_t y2 = y + h - 1;
          if (y2 >= 0) { // Not off top
            // Rectangle partly or fully overlaps screen
            if (x < 0) {
              x = 0;
              w = x2 + 1;
            } // Clip left
            if (y < 0) {
              y = 0;
              h = y2 + 1;
            } // Clip top
            if (x2 >= _width) {
              w = _width - x;
            } // Clip right
            if (y2 >= _height) {
              h = _height - y;
            } // Clip bottom
            for (int i = y; i < y + h; i++)
            {
                for (int j = x; j < x + w; j++)
                {
                    buffer->setColor(j + i * ST7735_TFTWIDTH_128, _color);
                }
            }
          }
        }
      }
    }
  }
}

void Painter::writeFastHLine(int16_t x, int16_t y, int16_t w,
                                            uint16_t _color) {
  if ((y >= 0) && (y < _height) && w) { // Y on screen, nonzero width
    if (w < 0) {                        // If negative width...
      x += w + 1;                       //   Move X to left edge
      w = -w;                           //   Use positive width
    }
    if (x < _width) { // Not off right
      int16_t x2 = x + w - 1;
      if (x2 >= 0) { // Not off left
        // Line partly or fully overlaps screen
        if (x < 0) {
          x = 0;
          w = x2 + 1;
        } // Clip left
        if (x2 >= _width) {
          w = _width - x;
        } // Clip right
        for (int i = y; i < y + 1; i++)
        {
            for (int j = x; j < x + w; j++)
            {
                buffer->setColor(j + i * ST7735_TFTWIDTH_128, _color);
            }
        }
      }
    }
  }
}

void Painter::writeFastVLine(int16_t x, int16_t y, int16_t h,
                                            uint16_t _color) {
  if ((x >= 0) && (x < _width) && h) { // X on screen, nonzero height
    if (h < 0) {                       // If negative height...
      y += h + 1;                      //   Move Y to top edge
      h = -h;                          //   Use positive height
    }
    if (y < _height) { // Not off bottom
      int16_t y2 = y + h - 1;
      if (y2 >= 0) { // Not off top
        // Line partly or fully overlaps screen
        if (y < 0) {
          y = 0;
          h = y2 + 1;
        } // Clip top
        if (y2 >= _height) {
          h = _height - y;
        } // Clip bottom
        for (int i = y; i < y + h; i++)
        {
            for (int j = x; j < x + 1; j++)
            {
                buffer->setColor(j + i * ST7735_TFTWIDTH_128, _color);
            }
        }
      }
    }
  }
}

void Painter::drawPixel(int16_t _x, int16_t _y, uint16_t _color) 
{
    writePixel(_x, _y, _color);
}

void Painter::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                               uint16_t color) {
    writeFillRect(x, y, w, h, color);
}

void Painter::drawFastHLine(int16_t x, int16_t y, int16_t w,
                                    uint16_t color) {
    writeFastHLine(x, y, w, color);
}

void Painter::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                    uint16_t color) {
    writeFastVLine(x, y, h, color);
}

void Painter::drawBuffer()
{
    int pixelChanged = 0;

    for (int i = 0; i < ST7735_TFTHEIGHT_160; i++)
    {
        for (int j = 0; j < ST7735_TFTWIDTH_128; j++)
        {
            int index = j + i * ST7735_TFTWIDTH_128;
            if (oldBuffer->getColor(index) != buffer->getColor(index) && buffer->getColor(index) != 0x000000)
            {
                pixelChanged++;
                diffBuffer->setColor(index, buffer->getColor(index));
            }
        }
    }

    startWriteReal();
    for (int i = 0; i < ST7735_TFTHEIGHT_160; i++)
    {
        for (int j = 0; j < ST7735_TFTWIDTH_128; j++)
        {
            uint16_t color(diffBuffer->getColor(j + i * ST7735_TFTWIDTH_128));
            // if (i == 1 && j == 1) { Serial.println(diffBuffer->getColor(j + i * ST7735_TFTWIDTH_128)); }
            if (color != Color(0, 0, 0).toUint16())
            {
                setAddrWindow(j, i, 1, 1);
                SPI_WRITE16(color);
            }
        }
    }
    endWriteReal();

    swap(oldBuffer, buffer);
    buffer->clearBuffer();
    diffBuffer->clearBuffer();
    // Serial.println(pixelChanged);
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

void Painter::paintRect(int _x, int _y, int _width, int _height, Color& _color)
{
    fillRect(_x, _y, _width, _height, _color.toUint16());
}

void Painter::paintBorder(int _x, int _y, int _width, int _height, Color& _color)
{
    drawRect(_x, _y, _width, _height, _color.toUint16());
}


void Painter::background(Color& _backgroundColor)
{
    fillScreen( _backgroundColor.getUint16() );
}

void Painter::setPaintColor(Color _drawColor)
{
    drawColor = std::make_unique<Color>(_drawColor);
}

Color Painter::getPaintColor()
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

void Painter::setTextSize(int _textSize)
{
    Adafruit_ST7735::setTextSize(_textSize);
}

void Painter::paintText(std::string _text, Point _positionPoint)
{
    setTextColor( drawColor->getUint16() );
    setCursor( _positionPoint.getX(), _positionPoint.getY() );
    // print(_text.c_str());
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

void Painter::paintLine(Point _pointA, Point _pointB)
{
    Adafruit_ST7735::drawLine( 
        _pointA.getX(), 
        _pointA.getY(), 
        _pointB.getX(), 
        _pointB.getY(), 
        drawColor->getUint16()
    );
}

void Painter::paintLine(int _x1, int _y1, int _x2, int _y2)
{
    Adafruit_ST7735::drawLine( 
        _x1, 
        _y1, 
        _x2, 
        _y2, 
        drawColor->getUint16()
    );
}

void Painter::paintLine(Point _pointA, Point _pointB, int _lineWidth)
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
        paintLine( 
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
