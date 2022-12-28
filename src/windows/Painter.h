#ifndef PAINTER_H
#define PAINTER_H

class Camera;
class Config;
class Color;
class Display;
class DisplayBuffer;
class GLFWwindow;
class Point;
class ResourceTheme;
class ShadersProcessor;
class Size;

#include <memory>
#include <string>

// This class is wrapper over the standart painter class. It was created for
// easy using our classes into drawing process.
class Painter
{
    private:
        const int DISPLAY_WIDTH; // for 1.44 and mini
        const int DISPLAY_HEIGHT; // for 1.8" and mini display
        const int BUFFER_SIZE = DISPLAY_WIDTH * DISPLAY_HEIGHT / 2;
        const int DISPLAY_SCALE;

        static std::shared_ptr<Painter> painter;
        GLFWwindow* window;
        std::shared_ptr<Camera> camera;
        unsigned int VBO, VAO;
        std::shared_ptr<ShadersProcessor> shadersProcessor;
        std::shared_ptr<ResourceTheme> currentResourceTheme;
        std::unique_ptr<Color> drawColor;
        int textSize;

        std::shared_ptr<DisplayBuffer> buffer;
        const static unsigned char font[];
        
        void writePixel(int16_t _x, int16_t _y, uint16_t _color);

        void writeFillRect(int16_t _x, int16_t _y, 
            int16_t _width, int16_t _height, uint16_t _color);

        void writeFastHLine(int16_t _x, int16_t _y, 
            int16_t _width, uint16_t _color);
        void writeFastVLine(int16_t _x, int16_t _y, 
            int16_t _height, uint16_t _color);
        void writeLine(int16_t _x0, int16_t _y0, 
            int16_t _x1, int16_t _y1, uint16_t _color);

        void writeChar(int16_t _x, int16_t _y, 
	        unsigned char _char, uint16_t _color, uint8_t _textSize);

        void writeChar(int16_t _x, int16_t _y, 
            unsigned char _char, uint16_t _color, uint16_t _background, 
            uint8_t _sizeX, uint8_t _sizeY);

        void writeText(int16_t _x, int16_t _y, 
            std::string _text, uint16_t _color, uint8_t _size);

        // Replace usual std::string to font-supported string.
        static std::string fromCyrilic(std::string _cyrilicString);

        void writeOpenGLBuffer();

    public:
        Painter(std::shared_ptr<Config> _config, GLFWwindow* _window, 
            std::shared_ptr<Camera> _camera);
        ~Painter();

        static void setDefault(std::shared_ptr<Painter> _painter);
        static std::shared_ptr<Painter> getPainter();

        void setResourceTheme(ResourceTheme _resourceTheme);
        const std::shared_ptr<ResourceTheme> getResourceTheme();

        void setPaintColor(Color _drawColor);
        Color getPaintColor();
        void setTextSize(int _textSize);

        void drawBuffer();

        void drawPixel(Point& _position);
        void drawLine(Point& _position1, Point& _position2);
        void drawLine(Point& _position1, Point& _position2, int _lineWidth);
        
        void drawRect(Point& _position, Size& _size);
        void drawRect(Point& _position, Size& _size, Color& _color);

        void drawBorder(Point& _position, Size& _size);
        void drawBorder(Point& _position, Size& _size, Color& _color);

        void drawText(Point& _position, std::string& _text);
        void clearScreen(Color& _backgroundColor);
        void testFont(int _fontPage);
        // Count how many letters can be contained into widget width.
        int countWrapSize(int _textSize, int _widgetWidth);
        // Return width of printing text string.
        Size countTextSize(std::string _text, int _textSize);
};

#endif
