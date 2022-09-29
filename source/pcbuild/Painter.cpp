#include "Painter.h"
#include "../Color.h"
#include "Camera.h"
#include "../DefineLog.h"
#include "../Point.h"
#include "../Size.h"
#include "../ResourceTheme.h"
#include "../StringUtf.h"
#include "ShadersProcessor.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Painter::Painter()
    :
    drawColor(std::make_unique<Color>(0, 0, 0)),
    textSize(1)
{
    shadersProcessor = std::make_shared<ShadersProcessor>();
    shadersProcessor->defaultShaders();
}

Painter::~Painter()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

std::shared_ptr<Painter> Painter::painter;

void Painter::drawBuffer()
{
    painter->swapBuffers();
}

void Painter::setDefault(std::shared_ptr<Painter> _painter)
{
    painter = _painter;
}

std::shared_ptr<Painter> Painter::getPainter()
{
    return painter;
}

void Painter::setWindow(GLFWwindow* _window)
{
    window = _window;
}

void Painter::swapBuffers()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Painter::setCamera(std::shared_ptr<Camera> _camera)
{
    camera = _camera;
}

void Painter::paintRect(int _x, int _y, int _width, int _height, Color& _color)
{
    // fillRect(_x, _y, _width, _height, _color.toUint16());
}

void Painter::paintBorder(int _x, int _y, int _width, int _height, Color& _color)
{
    // drawRect(_x, _y, _width, _height, _color.toUint16());
}


void Painter::background(Color& _backgroundColor)
{
    // fillScreen( _backgroundColor.getUint16() );
    glClearColor(
        (float)_backgroundColor.getR() / (float)255,
        (float)_backgroundColor.getR() / (float)255,
        (float)_backgroundColor.getR() / (float)255,
        1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Painter::setPaintColor(Color _drawColor)
{
    // drawColor = std::make_unique<Color>(_drawColor);
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
    textSize = _textSize;
}

void Painter::paintText(std::string _text, Point _positionPoint)
{
    // setTextColor( drawColor->getUint16() );
    // setCursor( _positionPoint.getX(), _positionPoint.getY() );
    // print( fromCyrilic(_text).c_str() );
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
    // Adafruit_ST7735::drawLine( 
    //     _pointA.getX(), 
    //     _pointA.getY(), 
    //     _pointB.getX(), 
    //     _pointB.getY(), 
    //     drawColor->getUint16()
    // );
    float vertices[] = {
        (float)_pointA.getX() / (float)128, (float)_pointA.getY() / (float)160, 0.0f,
        (float)_pointB.getX() / (float)128, (float)_pointB.getY() / (float)160, 0.0f,
    };
    
    unsigned int indices[] = {
        0, 1
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(shadersProcessor->getProgram(0));
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, -55.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(45.0f, (float)128 / (float)160, 0.1f, 100.0f);
    // glm::mat4 transform = glm::mat4(1.0f);
    // transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));

    // GLint transformLoc = glGetUniformLocation(pool->shadersProcessor->getProgram(0), "transform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    GLint modelLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    GLint viewLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
    GLint projectionLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
    Log::println("paintLine", "LOW");
}

void Painter::paintLine(int _x1, int _y1, int _x2, int _y2)
{
    // Adafruit_ST7735::drawLine( 
    //     _x1, 
    //     _y1, 
    //     _x2, 
    //     _y2, 
    //     drawColor->getUint16()
    // );
}

void Painter::paintLine(Point _pointA, Point _pointB, int _lineWidth)
{
    // int offsetX;
    // int offsetY;
    // if( _pointA.getY() == _pointB.getY() )
    // {
    //     offsetX = 0;
    //     offsetY = 1;
    // }
    // // else if( _pointA.getY() == _pointB.getY() )
    // else
    // {
    //     offsetX = 1;
    //     offsetY = 0;
    // }
    // for(int i = 0; i < _lineWidth; i++)
    // {
    //     paintLine( 
    //         Point( 
    //             _pointA.getX() + (i * offsetX), 
    //             _pointA.getY() + (i * offsetY) ), 
    //         Point( 
    //             _pointB.getX() + (i * offsetX), 
    //             _pointB.getY() + (i * offsetY) ) 
    //     );
    // }
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
