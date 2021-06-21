#ifndef PAINTER_H
#define PAINTER_H

class Color;
class Point;
class Size;
class ResourceTheme;
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <string>
#include <memory>

class Painter : public Adafruit_ST7735
{
    private:
        int pinDisplayCS;
        int pinDisplayDC;
        int pinDisplayRST;
        static std::shared_ptr<Painter> painter;
        std::shared_ptr<ResourceTheme> currentResourceTheme;
        std::unique_ptr<Color> drawColor;
        
    public:
        Painter(int _pinDisplayCS, int _pinDisplayDC, int _pinDisplayRST);
        ~Painter();
        static void setDefault(std::shared_ptr<Painter> _painter);
        static std::shared_ptr<Painter> getPainter();
        void background(Color _backgroundColor);
        void setDrawColor(Color _drawColor);
        Color getDrawColor();
        std::shared_ptr<ResourceTheme> getResourceTheme();
        void setResourceTheme(ResourceTheme _resourceTheme);
        void drawText(std::string _text, Point _positionPoint);
        static std::string fromCyrilic(std::string _cytilicString);
        void drawLine(Point _pointA, Point _pointB);
        void drawLine(Point _pointA, Point _pointB, int _lineWidth);
        void drawLine(int _x1, int _y1, int _x2, int _y2);

        int countWrapSize(int _textSize, int _widgetWidth);
        // bool isCharacterRussian(char* _letter);
        Size countTextSize(std::string _text, int _textSize);
};

#endif