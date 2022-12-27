#include "Painter.h"
#include "Color.h"
#include "Config.h"
#include "Camera.h"
#include "Log.h"
#include "DisplayBuffer.h"
#include "Point.h"
#include "Size.h"
#include "ResourceTheme.h"
#include "StringUtf.h"
#include "ShadersProcessor.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Painter::Painter(std::shared_ptr<Config> _config)
    :
    DISPLAY_WIDTH(_config->getDisplaySize().getWidth()),
    DISPLAY_HEIGHT(_config->getDisplaySize().getHeight()),
    DISPLAY_SCALE(_config->getDisplayScale()),
    drawColor(std::make_unique<Color>(0, 0, 0)),
    textSize(1),
    oldBuffer(std::make_shared<DisplayBuffer>(BUFFER_SIZE)),
    buffer(std::make_shared<DisplayBuffer>(BUFFER_SIZE)),
    diffBuffer(std::make_shared<DisplayBuffer>(BUFFER_SIZE))
{
    shadersProcessor = std::make_shared<ShadersProcessor>();
    shadersProcessor->defaultShaders();
}

Painter::~Painter()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

std::shared_ptr<Painter> Painter::painter;

void Painter::writePixel(int16_t _x, int16_t _y, uint16_t _color) 
{
    if ((_x >= 0) && (_x < DISPLAY_WIDTH) && (_y >= 0) && (_y < DISPLAY_HEIGHT)) 
    {
        buffer->setColor(_x + _y * DISPLAY_WIDTH, _color);
    }
}

void Painter::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                    uint16_t _color) {
  if (w && h) {   // Nonzero width and height?
    if (w < 0) {  // If negative width...
      x += w + 1; //   Move X to left edge
      w = -w;     //   Use positive width
    }
    if (x < DISPLAY_WIDTH) { // Not off right
      if (h < 0) {    // If negative height...
        y += h + 1;   //   Move Y to top edge
        h = -h;       //   Use positive height
      }
      if (y < DISPLAY_HEIGHT) { // Not off bottom
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
            if (x2 >= DISPLAY_WIDTH) {
              w = DISPLAY_WIDTH - x;
            } // Clip right
            if (y2 >= DISPLAY_HEIGHT) {
              h = DISPLAY_HEIGHT - y;
            } // Clip bottom
            for (int i = y; i < y + h; i++)
            {
                for (int j = x; j < x + w; j++)
                {
                    buffer->setColor(j + i * DISPLAY_WIDTH, _color);
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
  if ((y >= 0) && (y < DISPLAY_HEIGHT) && w) { // Y on screen, nonzero width
    if (w < 0) {                        // If negative width...
      x += w + 1;                       //   Move X to left edge
      w = -w;                           //   Use positive width
    }
    if (x < DISPLAY_WIDTH) { // Not off right
      int16_t x2 = x + w - 1;
      if (x2 >= 0) { // Not off left
        // Line partly or fully overlaps screen
        if (x < 0) {
          x = 0;
          w = x2 + 1;
        } // Clip left
        if (x2 >= DISPLAY_WIDTH) {
          w = DISPLAY_WIDTH - x;
        } // Clip right
        for (int i = y; i < y + 1; i++)
        {
            for (int j = x; j < x + w; j++)
            {
                buffer->setColor(j + i * DISPLAY_WIDTH, _color);
            }
        }
      }
    }
  }
}

void Painter::writeFastVLine(int16_t x, int16_t y, int16_t h,
                                            uint16_t _color) {
  if ((x >= 0) && (x < DISPLAY_WIDTH) && h) { // X on screen, nonzero height
    if (h < 0) {                       // If negative height...
      y += h + 1;                      //   Move Y to top edge
      h = -h;                          //   Use positive height
    }
    if (y < DISPLAY_HEIGHT) { // Not off bottom
      int16_t y2 = y + h - 1;
      if (y2 >= 0) { // Not off top
        // Line partly or fully overlaps screen
        if (y < 0) {
          y = 0;
          h = y2 + 1;
        } // Clip top
        if (y2 >= DISPLAY_HEIGHT) {
          h = DISPLAY_HEIGHT - y;
        } // Clip bottom
        for (int i = y; i < y + h; i++)
        {
            for (int j = x; j < x + 1; j++)
            {
                buffer->setColor(j + i * DISPLAY_WIDTH, _color);
            }
        }
      }
    }
  }
}

void _swap_int16_t(int16_t& _first, int16_t& _second) 
{
  int16_t temp = _first;
  _first = _second;
  _second = temp;
}

void Painter::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                            uint16_t color) {
  // Update in subclasses if desired!
  if (x0 == x1) {
    if (y0 > y1)
      _swap_int16_t(y0, y1);
    drawFastVLine(x0, y0, y1 - y0 + 1, color);
  } else if (y0 == y1) {
    if (x0 > x1)
      _swap_int16_t(x0, x1);
    drawFastHLine(x0, y0, x1 - x0 + 1, color);
  } else {
    writeLine(x0, y0, x1, y1, color);
  }
}

void Painter::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) 
{
#if defined(ESP8266)
  yield();
#endif
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    _swap_int16_t(x0, y0);
    _swap_int16_t(x1, y1);
  }

  if (x0 > x1) {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    if (steep) {
      writePixel(y0, x0, color);
    } else {
      writePixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
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

void Painter::drawChar(int16_t x, int16_t y, unsigned char c,
                            uint16_t color, uint8_t size) {
  drawChar(x, y, c, color, color, size, size);
}

void Painter::drawChar(int16_t x, int16_t y, unsigned char c,
                            uint16_t color, uint16_t bg, uint8_t size_x,
                            uint8_t size_y) {
    if ((x >= DISPLAY_WIDTH) ||              // Clip right
        (y >= DISPLAY_HEIGHT) ||             // Clip bottom
        ((x + 6 * size_x - 1) < 0) || // Clip left
        ((y + 8 * size_y - 1) < 0))   // Clip top
      return;

    for (int i = 0; i < 5; i++) { // Char bitmap = 5 columns
      uint8_t line = font[c * 5 + i];
      for (int j = 0; j < 8; j++, line >>= 1) {
        if (line & 1) {
          if (size_x == 1 && size_y == 1) {
            writePixel(x + i, y + j, color);
            // std::cout << "x: " << x + i << " y: " << y + j << std::endl;
        } else
            writeFillRect(x + i * size_x, y + j * size_y, size_x, size_y, color);
        } /**else if (bg != color) {
          if (size_x == 1 && size_y == 1)
            writePixel(x + i, y + j, bg);
          else
            writeFillRect(x + i * size_x, y + j * size_y, size_x, size_y, bg);
        }**/
      }
    }
    /**if (bg != color) { // If opaque, draw vertical line for last column
      if (size_x == 1 && size_y == 1)
        writeFastVLine(x + 5, y, 8, bg);
      else
        writeFillRect(x + 5 * size_x, y, size_x, 8 * size_y, bg);
    }**/
}

void Painter::drawText(int16_t x, int16_t y, std::string text, uint16_t color, 
    uint8_t size)
{
    std::string cyrilicText = fromCyrilic(text);
    // std::cout << cyrilicText << std::endl;
    for (int i = 0; i < cyrilicText.size(); i++) {
        painter->drawChar(x + (i * ((5 * size) + size)), y, cyrilicText[i], color, size);
    }
}

void Painter::testFont(int _fontPage)
{
    int gridSize = 16;
    int charOffset = 225 * _fontPage;
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            std::cout << charOffset +(gridSize*i+j) << " " << char(charOffset +(gridSize*i+j)) << std::endl;
            drawChar(10 + i*6*1, 10 + j*8*1, char(charOffset +(gridSize*i+j)), painter->getResourceTheme()->getFocusColor().toUint16(), 1);
        }
    }
}

void Painter::drawBuffer()
{
    int pixelChanged = 0;

    // for (int i = 0; i < DISPLAY_HEIGHT; i++)
    // {
    //     for (int j = 0; j < DISPLAY_WIDTH; j++)
    //     {
    //         int index = j + i * DISPLAY_WIDTH;
    //         if (oldBuffer->getColor(index) != buffer->getColor(index) && buffer->getColor(index) != 0x000000)
    //         {
    //             pixelChanged++;
    //             diffBuffer->setColor(index, buffer->getColor(index));
    //         }
    //     }
    // }

    // startWriteReal();
    // for (int i = 0; i < DISPLAY_HEIGHT; i++)
    // {
    //     for (int j = 0; j < DISPLAY_WIDTH; j++)
    //     {
    //         uint16_t color(buffer->getColor(j + i * DISPLAY_WIDTH));
    //         // if (i == 1 && j == 1) { Serial.println(diffBuffer->getColor(j + i * DISPLAY_WIDTH)); }
    //         if (color != Color(0, 0, 0).toUint16())
    //         {
    //             drawOpenGLPixel(j, i, color);
    //         }
    //     }
    // }

    drawOpenGLBuffer();
    
    // endWriteReal();

    // swap(oldBuffer, buffer);
    // buffer->clearBuffer();
    // diffBuffer->clearBuffer();

    swapBuffers();
    // glfwSwapBuffers(window);
    // Serial.println(pixelChanged);
}

void Painter::drawOpenGLPixel(int _x, int _y, uint16_t _color)
{
    // // Log::println("drawPixel", "LOW");
    // float vertices[] = {
    //     (float)_x / (float)128, (float)_y / (float)160, 0.0f
    // };
    
    // // unsigned int indices[] = {
    // //     0
    // // };
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // glUseProgram(shadersProcessor->getProgram(0));
    // glm::mat4 model = glm::mat4(1.0f);
    // //model = glm::rotate(model, -55.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    // // glm::mat4 view = glm::mat4(1.0f);
    // // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
    // glm::mat4 projection = glm::mat4(1.0f);
    // projection = glm::perspective(45.0f, (float)128 / (float)160, 0.1f, 100.0f);
    // // glm::mat4 transform = glm::mat4(1.0f);
    // // transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));

    // // GLint transformLoc = glGetUniformLocation(pool->shadersProcessor->getProgram(0), "transform");
    // // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    // GLint modelLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "model");
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // GLint viewLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "view");
    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
    // GLint projectionLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "projection");
    // glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // glBindVertexArray(VAO);
    // // glEnable(GL_DEPTH_TEST);
    // // glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_POINTS, 0, 1);
}

void Painter::drawOpenGLBuffer()
{
    // Color c(buffer->getColor(0 + 0 * DISPLAY_WIDTH));
    // std::cout << c.getR() << " " << c.getG() << " " << c.getB() << std::endl;
    float vertices[DISPLAY_WIDTH * DISPLAY_HEIGHT * 5];

    int verticesIndex = 0;
    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
        for (int j = 0; j < DISPLAY_WIDTH; j++)
        {
            // std::cout << buffer->getColor(j + i * DISPLAY_WIDTH) << " ";
            uint16_t color(buffer->getColor(j + i * DISPLAY_WIDTH));
            Color rgbColor(color);
            vertices[verticesIndex * 5 + 0] = (float)j / (float)DISPLAY_WIDTH;
            vertices[verticesIndex * 5 + 1] = (float)i / (float)DISPLAY_HEIGHT;
            vertices[verticesIndex * 5 + 2] = (float)rgbColor.getR() / 255;
            vertices[verticesIndex * 5 + 3] = (float)rgbColor.getG() / 255;
            vertices[verticesIndex * 5 + 4] = (float)rgbColor.getB() / 255;
            // vertices[verticesIndex * 5 + 2] = (float)i/255;
            // vertices[verticesIndex * 5 + 3] = (float)i/255;
            // vertices[verticesIndex * 5 + 4] = (float)i/255;
            verticesIndex++;
        }
        // std::cout << std::endl;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO);

    glUseProgram(shadersProcessor->getProgram(0));

    glm::mat4 model = glm::mat4(1.0f);
    GLint modelLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    GLint viewLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));

    glBindVertexArray(VAO);
    glPointSize(DISPLAY_SCALE);
    glDrawArrays(GL_POINTS, 0, DISPLAY_WIDTH * DISPLAY_HEIGHT);
    glBindVertexArray(0);
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
    // std::cout << "glfwPollEvents()" << std::endl;
}

void Painter::setCamera(std::shared_ptr<Camera> _camera)
{
    camera = _camera;
}

void Painter::paintRect(int _x, int _y, int _width, int _height, Color& _color)
{
    fillRect(_x, _y, _width, _height, _color.toUint16());
}

void Painter::paintBorder(int _x, int _y, int _width, int _height, Color& _color)
{
    // drawRect(_x, _y, _width, _height, _color.toUint16());
}

void Painter::background(Color& _backgroundColor)
{
    // std::shared_ptr<DisplayBuffer> test = std::make_shared<DisplayBuffer>(5);
    // test->test(_backgroundColor.toUint16());
    // // std::cout << "background res: " << buffer->getColor(0) << std::endl;
    // std::cout << "background: " << _backgroundColor.toUint16() << std::endl;
    writeFillRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, _backgroundColor.toUint16());
    // std::cout << "background res: " << buffer->getColor(0) << std::endl;
}

// void Painter::paintRect(int _x, int _y, int _width, int _height, Color& _color)
// {
//     // fillRect(_x, _y, _width, _height, _color.toUint16());
// }

// void Painter::paintBorder(int _x, int _y, int _width, int _height, Color& _color)
// {
//     // drawRect(_x, _y, _width, _height, _color.toUint16());
// }


// void Painter::background(Color& _backgroundColor)
// {
//     // fillScreen( _backgroundColor.getUint16() );
//     glClearColor(
//         (float)_backgroundColor.getR() / (float)255,
//         (float)_backgroundColor.getR() / (float)255,
//         (float)_backgroundColor.getR() / (float)255,
//         1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// }

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
    textSize = _textSize;
}

void Painter::drawText(Point _positionPoint, std::string _text)
{
    // setTextColor( drawColor->getUint16() );
    drawText(_positionPoint.getX(), _positionPoint.getY(), _text, drawColor->toUint16(), textSize);
    // setCursor( _positionPoint.getX(), _positionPoint.getY() );
    // print( fromCyrilic(_text).c_str() );
    // Maybe we can do only print( _text.c_str() ); if text only English. 
}

std::string Painter::fromCyrilic(std::string _cyrilicString)
{
    // for (int i = 0; i < _cyrilicString.size(); i++) {
    //     std::cout << int(_cyrilicString[i]) << " ";
    // }
    int i;
    int k;
    std::string target;
    unsigned char n;
    char m[2] = { '0', '\0' };

    k = _cyrilicString.length();
    i = 0;

    while (i < k) {
        n = _cyrilicString[i]; 
        i++;

        if (n >= 0xC0) {
            switch (n) {
                case 0xD0: {
                    // std::cout << "0xD0" << std::endl;
                    n = _cyrilicString[i]; 
                    i++;
                    if (n == 0x81) { n = 0xA9; break; }
                    if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
                    break;
                }
                case 0xD1: {
                    // std::cout << "0xD1" << std::endl;
                    n = _cyrilicString[i]; 
                    i++;
                    if (n == 0x91) { n = 0xB9; break; }
                    if (n >= 0x80 && n <= 0x8F) { n = n + 0x70; }
                    break;
                }
            }
        }
        m[0] = n; 
        target = target + std::string(m);
    }
    return target;
}

// void Painter::paintLine(Point _pointA, Point _pointB)
// {
//     // Adafruit_ST7735::drawLine( 
//     //     _pointA.getX(), 
//     //     _pointA.getY(), 
//     //     _pointB.getX(), 
//     //     _pointB.getY(), 
//     //     drawColor->getUint16()
//     // );
//     float vertices[] = {
//         (float)_pointA.getX() / (float)128, (float)_pointA.getY() / (float)160, 0.0f,
//         (float)_pointB.getX() / (float)128, (float)_pointB.getY() / (float)160, 0.0f,
//     };
    
//     unsigned int indices[] = {
//         0, 1
//     };
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
//     glUseProgram(shadersProcessor->getProgram(0));
//     glm::mat4 model = glm::mat4(1.0f);
//     //model = glm::rotate(model, -55.0f, glm::vec3(0.0f, 0.0f, 1.0f));
//     // glm::mat4 view = glm::mat4(1.0f);
//     // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
//     glm::mat4 projection = glm::mat4(1.0f);
//     projection = glm::perspective(45.0f, (float)128 / (float)160, 0.1f, 100.0f);
//     // glm::mat4 transform = glm::mat4(1.0f);
//     // transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));

//     // GLint transformLoc = glGetUniformLocation(pool->shadersProcessor->getProgram(0), "transform");
//     // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
//     GLint modelLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "model");
//     glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//     GLint viewLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "view");
//     glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
//     GLint projectionLoc = glGetUniformLocation(shadersProcessor->getProgram(0), "projection");
//     glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

//     glBindVertexArray(VAO);
//     glEnable(GL_DEPTH_TEST);
//     glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
//     glfwSwapBuffers(window);
//     glfwPollEvents();
//     Log::println("paintLine", "LOW");
// }

void Painter::drawLine(Point _pointA, Point _pointB)
{
    drawLine( 
        _pointA.getX(), 
        _pointA.getY(), 
        _pointB.getX(), 
        _pointB.getY(), 
        drawColor->getUint16()
    );
}

// void Painter::paintLine(int _x1, int _y1, int _x2, int _y2)
// {
//     // Adafruit_ST7735::drawLine( 
//     //     _x1, 
//     //     _y1, 
//     //     _x2, 
//     //     _y2, 
//     //     drawColor->getUint16()
//     // );
// }

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

const unsigned char Painter::font[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 
0x3E, 0x55, 0x51, 0x55, 0x3E, 
0x3E, 0x6B, 0x6F, 0x6B, 0x3E, 
0x0C, 0x1E, 0x3C, 0x1E, 0x0C, 
0x08, 0x1C, 0x3E, 0x1C, 0x08, 
0x1C, 0x4A, 0x7F, 0x4A, 0x1C, 
0x18, 0x5C, 0x7F, 0x5C, 0x18, 
0x00, 0x1C, 0x1C, 0x1C, 0x00, 
0x7F, 0x63, 0x63, 0x63, 0x7F, 
0x00, 0x1C, 0x14, 0x1C, 0x00, 
0x7F, 0x63, 0x6B, 0x63, 0x7F, 
0x30, 0x48, 0x4D, 0x33, 0x07, 
0x06, 0x29, 0x79, 0x29, 0x06, 
0x20, 0x50, 0x3F, 0x02, 0x0C, 
0x60, 0x7F, 0x05, 0x35, 0x3F, 
0x2A, 0x1C, 0x77, 0x1C, 0x2A, 
0x00, 0x7F, 0x3E, 0x1C, 0x08, 
0x08, 0x1C, 0x3E, 0x7F, 0x00, 
0x14, 0x22, 0x7F, 0x22, 0x14, 
0x00, 0x5F, 0x00, 0x5F, 0x00, 
0x06, 0x09, 0x7F, 0x01, 0x7F, 
0x4A, 0x55, 0x55, 0x55, 0x29, 
0x60, 0x60, 0x60, 0x60, 0x60, 
0x54, 0x62, 0x7F, 0x62, 0x54, 
0x08, 0x04, 0x7E, 0x04, 0x08, 
0x08, 0x10, 0x3F, 0x10, 0x08, 
0x08, 0x08, 0x2A, 0x1C, 0x08, 
0x08, 0x1C, 0x2A, 0x08, 0x08, 
0x1C, 0x10, 0x10, 0x10, 0x10, 
0x1C, 0x3E, 0x08, 0x3E, 0x1C, 
0x30, 0x3C, 0x3F, 0x3C, 0x30, 
0x06, 0x1E, 0x7E, 0x1E, 0x06, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x5F, 0x00, 0x00, 
0x00, 0x07, 0x00, 0x07, 0x00, 
0x14, 0x7F, 0x14, 0x7F, 0x14, 
0x24, 0x2A, 0x7F, 0x2A, 0x12, 
0x23, 0x13, 0x08, 0x64, 0x62, 
0x36, 0x49, 0x56, 0x20, 0x50, 
0x00, 0x00, 0x07, 0x00, 0x00, 
0x00, 0x1C, 0x22, 0x41, 0x00, 
0x00, 0x41, 0x22, 0x1C, 0x00, 
0x14, 0x08, 0x3E, 0x08, 0x14, 
0x08, 0x08, 0x3E, 0x08, 0x08, 
0x00, 0xA0, 0x60, 0x00, 0x00, 
0x08, 0x08, 0x08, 0x08, 0x08, 
0x00, 0x60, 0x60, 0x00, 0x00, 
0x20, 0x10, 0x08, 0x04, 0x02, 
0x3E, 0x51, 0x49, 0x45, 0x3E, 
0x44, 0x42, 0x7F, 0x40, 0x40, 
0x42, 0x61, 0x51, 0x49, 0x46, 
0x21, 0x41, 0x45, 0x4B, 0x31, 
0x18, 0x14, 0x12, 0x7F, 0x10, 
0x27, 0x45, 0x45, 0x45, 0x39, 
0x3C, 0x4A, 0x49, 0x49, 0x30, 
0x01, 0x71, 0x09, 0x05, 0x03, 
0x36, 0x49, 0x49, 0x49, 0x36, 
0x06, 0x49, 0x49, 0x29, 0x1E, 
0x00, 0x6C, 0x6C, 0x00, 0x00, 
0x00, 0xAC, 0x6C, 0x00, 0x00, 
0x08, 0x14, 0x22, 0x41, 0x00, 
0x14, 0x14, 0x14, 0x14, 0x14, 
0x00, 0x41, 0x22, 0x14, 0x08, 
0x02, 0x01, 0x51, 0x09, 0x06, 
0x3E, 0x41, 0x5D, 0x55, 0x5E, 
0x7C, 0x12, 0x11, 0x12, 0x7C, 
0x7F, 0x49, 0x49, 0x49, 0x36, 
0x3E, 0x41, 0x41, 0x41, 0x22, 
0x7F, 0x41, 0x41, 0x22, 0x1C, 
0x7F, 0x49, 0x49, 0x49, 0x41, 
0x7F, 0x09, 0x09, 0x09, 0x01, 
0x3E, 0x41, 0x49, 0x49, 0x7A, 
0x7F, 0x08, 0x08, 0x08, 0x7F, 
0x00, 0x41, 0x7F, 0x41, 0x00, 
0x20, 0x40, 0x41, 0x3F, 0x01, 
0x7F, 0x08, 0x14, 0x22, 0x41, 
0x7F, 0x40, 0x40, 0x40, 0x60, 
0x7F, 0x02, 0x0C, 0x02, 0x7F, 
0x7F, 0x04, 0x08, 0x10, 0x7F, 
0x3E, 0x41, 0x41, 0x41, 0x3E, 
0x7F, 0x09, 0x09, 0x09, 0x06, 
0x3E, 0x41, 0x51, 0x21, 0x5E, 
0x7F, 0x09, 0x19, 0x29, 0x46, 
0x46, 0x49, 0x49, 0x49, 0x31, 
0x03, 0x01, 0x7F, 0x01, 0x03, 
0x3F, 0x40, 0x40, 0x40, 0x3F, 
0x1F, 0x20, 0x40, 0x20, 0x1F, 
0x3F, 0x40, 0x3C, 0x40, 0x3F, 
0x63, 0x14, 0x08, 0x14, 0x63, 
0x07, 0x08, 0x70, 0x08, 0x07, 
0x61, 0x51, 0x49, 0x45, 0x43, 
0x00, 0x7F, 0x41, 0x41, 0x00, 
0x02, 0x04, 0x08, 0x10, 0x20, 
0x00, 0x41, 0x41, 0x7F, 0x00, 
0x04, 0x02, 0x01, 0x02, 0x04, 
0x40, 0x40, 0x40, 0x40, 0x40, 
0x00, 0x01, 0x02, 0x04, 0x00, 
0x20, 0x54, 0x54, 0x54, 0x78, 
0x7F, 0x48, 0x44, 0x44, 0x38, 
0x38, 0x44, 0x44, 0x44, 0x48, 
0x38, 0x44, 0x44, 0x48, 0x7F, 
0x38, 0x54, 0x54, 0x54, 0x18, 
0x08, 0x7E, 0x09, 0x01, 0x02, 
0x08, 0x54, 0x54, 0x58, 0x3C, 
0x7F, 0x08, 0x04, 0x04, 0x78, 
0x00, 0x44, 0x7D, 0x40, 0x00, 
0x20, 0x40, 0x44, 0x3D, 0x00, 
0x7F, 0x10, 0x10, 0x28, 0x44, 
0x00, 0x41, 0x7F, 0x40, 0x00, 
0x7C, 0x04, 0x78, 0x04, 0x78, 
0x7C, 0x08, 0x04, 0x04, 0x78, 
0x38, 0x44, 0x44, 0x44, 0x38, 
0x7C, 0x14, 0x14, 0x14, 0x08, 
0x08, 0x14, 0x14, 0x0C, 0x7C, 
0x7C, 0x08, 0x04, 0x04, 0x08, 
0x48, 0x54, 0x54, 0x54, 0x24, 
0x04, 0x3F, 0x44, 0x40, 0x20, 
0x3C, 0x40, 0x40, 0x20, 0x7C, 
0x1C, 0x20, 0x40, 0x20, 0x1C, 
0x3C, 0x40, 0x38, 0x40, 0x3C, 
0x44, 0x28, 0x10, 0x28, 0x44, 
0x0C, 0x50, 0x50, 0x50, 0x3C, 
0x44, 0x64, 0x54, 0x4C, 0x44, 
0x00, 0x08, 0x36, 0x41, 0x00, 
0x00, 0x00, 0x7F, 0x00, 0x00, 
0x00, 0x41, 0x36, 0x08, 0x00, 
0x02, 0x01, 0x02, 0x04, 0x02, 
0x70, 0x48, 0x44, 0x48, 0x70, 
0x00, 0x0E, 0x11, 0x0E, 0x00, 
0x00, 0x12, 0x1F, 0x10, 0x00, 
0x00, 0x12, 0x19, 0x16, 0x00, 
0x00, 0x11, 0x15, 0x0B, 0x00, 
0x00, 0x07, 0x04, 0x1F, 0x00, 
0x00, 0x17, 0x15, 0x09, 0x00, 
0x00, 0x0E, 0x15, 0x09, 0x00, 
0x00, 0x01, 0x1D, 0x03, 0x00, 
0x00, 0x0A, 0x15, 0x0A, 0x00, 
0x00, 0x12, 0x15, 0x0E, 0x00, 
0x00, 0x04, 0x04, 0x04, 0x00, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0x3E, 0x00, 0x00, 0x00, 0x00, 
0x3E, 0x3E, 0x00, 0x00, 0x00, 
0x3E, 0x3E, 0x00, 0x3E, 0x00, 
0x3E, 0x3E, 0x00, 0x3E, 0x3E, 
0x80, 0x80, 0x80, 0x80, 0x80, 
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 
0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 
0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 
0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 
0xDB, 0xDB, 0xDB, 0xDB, 0xDB, 
0x40, 0x00, 0x40, 0x00, 0x40, 
0x60, 0x00, 0x40, 0x00, 0x40, 
0x60, 0x00, 0x70, 0x00, 0x40, 
0x60, 0x00, 0x70, 0x00, 0x78, 
0x7C, 0x00, 0x40, 0x00, 0x40, 
0x7C, 0x00, 0x7E, 0x00, 0x40, 
0x7C, 0x00, 0x7E, 0x00, 0x7F, 
0x1C, 0x77, 0x41, 0x41, 0x41, 
0x41, 0x41, 0x41, 0x41, 0x41, 
0x41, 0x41, 0x41, 0x7F, 0x00, 
0x1C, 0x77, 0x41, 0x5D, 0x5D, 
0x41, 0x41, 0x41, 0x5D, 0x5D, 
0x5D, 0x5D, 0x41, 0x5D, 0x5D, 
0x5D, 0x5D, 0x41, 0x7F, 0x00, 
0x22, 0x1C, 0x14, 0x1C, 0x22, 
0x00, 0x08, 0x1C, 0x08, 0x00, 
0x00, 0x00, 0x77, 0x00, 0x00, 
0x46, 0x5D, 0x55, 0x5D, 0x31, 
0x7C, 0x55, 0x54, 0x55, 0x44, 
0x08, 0x08, 0x2A, 0x08, 0x08, 
0x00, 0x14, 0x08, 0x14, 0x00, 
0x08, 0x14, 0x22, 0x08, 0x14, 
0x7F, 0x41, 0x71, 0x31, 0x1F, 
0x03, 0x05, 0x7F, 0x05, 0x03, 
0x22, 0x14, 0x7F, 0x55, 0x22, 
0x02, 0x55, 0x7D, 0x05, 0x02, 
0x06, 0x09, 0x09, 0x06, 0x00, 
0x44, 0x44, 0x5F, 0x44, 0x44, 
0x1C, 0x14, 0x1C, 0x22, 0x7F, 
0x20, 0x3E, 0x61, 0x3E, 0x20, 
0x20, 0x50, 0x3F, 0x02, 0x0C, 
0x80, 0x7C, 0x20, 0x3C, 0x40, 
0x44, 0x3C, 0x04, 0x7C, 0x44, 
0x00, 0x00, 0x08, 0x00, 0x00, 
0x38, 0x55, 0x54, 0x55, 0x18, 
0x7E, 0x08, 0x10, 0x7F, 0x01, 
0x08, 0x10, 0x08, 0x04, 0x02, 
0x14, 0x08, 0x22, 0x14, 0x08, 
0x0E, 0x06, 0x0A, 0x10, 0x20, 
0x20, 0x10, 0x0A, 0x06, 0x0E, 
0x38, 0x30, 0x28, 0x04, 0x02, 
0x02, 0x04, 0x28, 0x30, 0x38, 
0x7E, 0x11, 0x11, 0x11, 0x7E, 
0x7F, 0x49, 0x49, 0x49, 0x31, 
0x7F, 0x49, 0x49, 0x49, 0x36, 
0x7F, 0x01, 0x01, 0x01, 0x03, 
0xC0, 0x7F, 0x41, 0x7F, 0xC0, 
0x7F, 0x49, 0x49, 0x49, 0x41, 
0x77, 0x08, 0x7F, 0x08, 0x77, 
0x41, 0x49, 0x49, 0x49, 0x36, 
0x7F, 0x10, 0x08, 0x04, 0x7F, 
0x7C, 0x21, 0x12, 0x09, 0x7C, 
0x7F, 0x08, 0x14, 0x22, 0x41, 
0x40, 0x3E, 0x01, 0x01, 0x7F, 
0x7F, 0x02, 0x0C, 0x02, 0x7F, 
0x7F, 0x08, 0x08, 0x08, 0x7F, 
0x3E, 0x41, 0x41, 0x41, 0x3E, 
0x7F, 0x01, 0x01, 0x01, 0x7F, 
0x7F, 0x09, 0x09, 0x09, 0x06, 
0x3E, 0x41, 0x41, 0x41, 0x22, 
0x01, 0x01, 0x7F, 0x01, 0x01, 
0x07, 0x48, 0x48, 0x48, 0x3F, 
0x0E, 0x11, 0x7F, 0x11, 0x0E, 
0x63, 0x14, 0x08, 0x14, 0x63, 
0x7F, 0x40, 0x40, 0x7F, 0xC0, 
0x07, 0x08, 0x08, 0x08, 0x7F, 
0x7F, 0x40, 0x7F, 0x40, 0x7F, 
0x7F, 0x40, 0x7F, 0x40, 0xFF, 
0x01, 0x7F, 0x48, 0x48, 0x30, 
0x7F, 0x48, 0x48, 0x30, 0x7F, 
0x7F, 0x48, 0x48, 0x48, 0x30, 
0x22, 0x41, 0x49, 0x49, 0x3E, 
0x7F, 0x08, 0x3E, 0x41, 0x3E, 
0x46, 0x29, 0x19, 0x09, 0x7F, 
0x20, 0x54, 0x54, 0x54, 0x78, 
0x3C, 0x4A, 0x4A, 0x49, 0x31, 
0x7C, 0x54, 0x54, 0x54, 0x28, 
0x7C, 0x04, 0x04, 0x04, 0x0C, 
0xC0, 0x78, 0x44, 0x7C, 0xC0, 
0x38, 0x54, 0x54, 0x54, 0x18, 
0x6C, 0x10, 0x7C, 0x10, 0x6C, 
0x44, 0x54, 0x54, 0x54, 0x28, 
0x7C, 0x20, 0x10, 0x08, 0x7C, 
0x7C, 0x40, 0x26, 0x10, 0x7C, 
0x7C, 0x10, 0x10, 0x28, 0x44, 
0x40, 0x38, 0x04, 0x04, 0x7C, 
0x7C, 0x08, 0x10, 0x08, 0x7C, 
0x7C, 0x10, 0x10, 0x10, 0x7C, 
0x38, 0x44, 0x44, 0x44, 0x38, 
0x7C, 0x04, 0x04, 0x04, 0x7C, 
0x7C, 0x14, 0x14, 0x14, 0x08, 
0x38, 0x44, 0x44, 0x44, 0x48, 
0x04, 0x04, 0x7C, 0x04, 0x04, 
0x0C, 0x50, 0x50, 0x50, 0x3C, 
0x18, 0x24, 0xFC, 0x24, 0x18, 
0x44, 0x28, 0x10, 0x28, 0x44, 
0x7C, 0x40, 0x40, 0x7C, 0xC0, 
0x0C, 0x10, 0x10, 0x10, 0x7C, 
0x7C, 0x40, 0x7C, 0x40, 0x7C, 
0x7C, 0x40, 0x7C, 0x40, 0xFC, 
0x04, 0x7C, 0x50, 0x50, 0x20, 
0x7C, 0x50, 0x50, 0x20, 0x7C, 
0x7C, 0x50, 0x50, 0x50, 0x20, 
0x28, 0x44, 0x54, 0x54, 0x38, 
0x7C, 0x10, 0x38, 0x44, 0x38, 
0x48, 0x34, 0x14, 0x14, 0x7C
};
