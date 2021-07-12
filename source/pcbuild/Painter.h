#ifndef PAINTER_H
#define PAINTER_H

class Color;
class GLFWwindow;
class Point;
class ResourceTheme;
class Size;

#include <memory>
#include <string>

// This class is wrapper over the standart painter class. It was created for
// easy using our classes into drawing process.
class Painter
{
    private:
        GLFWwindow* window;
        int pinDisplayCS;
        int pinDisplayDC;
        int pinDisplayRST;
        static std::shared_ptr<Painter> painter;
        std::shared_ptr<ResourceTheme> currentResourceTheme;
        std::unique_ptr<Color> drawColor;
        int textSize;
        
    public:
        Painter();
        ~Painter();
        static void setDefault(std::shared_ptr<Painter> _painter);
        static std::shared_ptr<Painter> getPainter();
        void setWindow(GLFWwindow* _window);
        
        void background(Color& _backgroundColor);

        void paintRect(int _x, int _y, int _width, int _height, Color& _color);
        void paintBorder(int _x, int _y, int _width, int _height, Color& _color);

        void setPaintColor(Color _drawColor);
        Color getPaintColor();

        std::shared_ptr<ResourceTheme> getResourceTheme();
        void setResourceTheme(ResourceTheme _resourceTheme);

        void setTextSize(int _textSize);
        void paintText(std::string _text, Point _positionPoint);
        // Maybe it need to be moved 
        static std::string fromCyrilic(std::string _cytilicString);

        void paintLine(Point _pointA, Point _pointB);
        void paintLine(Point _pointA, Point _pointB, int _lineWidth);
        void paintLine(int _x1, int _y1, int _x2, int _y2);

        // This function count how many letters can be contained into widget width.
        int countWrapSize(int _textSize, int _widgetWidth);
        // This function return width of printing text string.
        Size countTextSize(std::string _text, int _textSize);
};

#endif
