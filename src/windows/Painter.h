#ifndef PAINTER_H
#define PAINTER_H

class Camera;
class Color;
class DisplayBuffer;
class GLFWwindow;
class Point;
class ResourceTheme;
class ShadersProcessor;
class Size;

#include <memory>
#include <string>

#define ST7735_TFTWIDTH_128 128  // for 1.44 and mini
#define ST7735_TFTHEIGHT_160 160 // for 1.8" and mini display
const int bufferSize = ST7735_TFTWIDTH_128 * ST7735_TFTHEIGHT_160 / 2;

// This class is wrapper over the standart painter class. It was created for
// easy using our classes into drawing process.
class Painter
{
    private:
        GLFWwindow* window;
        std::shared_ptr<Camera> camera;
        unsigned int VBO, VAO, EBO;
        std::shared_ptr<ShadersProcessor> shadersProcessor;
        int pinDisplayCS;
        int pinDisplayDC;
        int pinDisplayRST;
        static std::shared_ptr<Painter> painter;
        std::shared_ptr<ResourceTheme> currentResourceTheme;
        std::unique_ptr<Color> drawColor;
        int textSize;

        std::shared_ptr<DisplayBuffer> oldBuffer;
        std::shared_ptr<DisplayBuffer> buffer;
        std::shared_ptr<DisplayBuffer> diffBuffer;
        const static unsigned char font[];
        
    public:
        Painter();
        ~Painter();

        void writePixel(int16_t x, int16_t y, uint16_t _color);
        void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t _color);
        void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t _color);
        void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t _color);
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
            uint8_t size);
        void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
            uint16_t bg, uint8_t size_x, uint8_t size_y);
        void drawText(int16_t x, int16_t y, std::string text, uint16_t color, 
            uint8_t size);

        void drawBuffer();
        void drawOpenGLPixel(int _x, int _y, uint16_t _color);
        void drawOpenGLBuffer();

        static void setDefault(std::shared_ptr<Painter> _painter);
        static std::shared_ptr<Painter> getPainter();
        void setWindow(GLFWwindow* _window);
        
        void swapBuffers();
        void setCamera(std::shared_ptr<Camera> _camera);

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

        // void paintLine(Point _pointA, Point _pointB);
        // void paintLine(Point _pointA, Point _pointB, int _lineWidth);
        // void paintLine(int _x1, int _y1, int _x2, int _y2);

        // This function count how many letters can be contained into widget width.
        int countWrapSize(int _textSize, int _widgetWidth);
        // This function return width of printing text string.
        Size countTextSize(std::string _text, int _textSize);
};

#endif
