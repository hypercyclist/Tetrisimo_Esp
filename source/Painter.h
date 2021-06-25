#ifndef PAINTER_H
#define PAINTER_H

class Color;
class Point;
class ResourceTheme;
class Size;

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <memory>
#include <string>

// This class is wrapper over the standart painter class. It was created for
// easy using our classes into drawing process.
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

        // This function count how many letters can be contained into widget width.
        int countWrapSize(int _textSize, int _widgetWidth);
        // This function return width of printing text string.
        Size countTextSize(std::string _text, int _textSize);
};

#endif
