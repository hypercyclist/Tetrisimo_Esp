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

Painter::Painter(std::shared_ptr<Config> _config, GLFWwindow* _window, 
	std::shared_ptr<Camera> _camera)
    :
    DISPLAY_WIDTH(_config->getDisplaySize().getWidth()),
    DISPLAY_HEIGHT(_config->getDisplaySize().getHeight()),
    DISPLAY_SCALE(_config->getDisplayScale()),
    drawColor(std::make_unique<Color>(0, 0, 0)),
    textSize(1),
    buffer(std::make_shared<DisplayBuffer>(BUFFER_SIZE)),
	window(_window),
	camera(_camera)
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

void Painter::setDefault(std::shared_ptr<Painter> _painter) 
{ 
	painter = _painter;
}

std::shared_ptr<Painter> Painter::getPainter()
{
    return painter;
}

void Painter::setResourceTheme(ResourceTheme _resourceTheme)
{
    currentResourceTheme = std::make_shared<ResourceTheme>(_resourceTheme);
}

const std::shared_ptr<ResourceTheme> Painter::getResourceTheme()
{
    return currentResourceTheme;
}

void Painter::setPaintColor(Color _drawColor)
{
    drawColor = std::make_unique<Color>(_drawColor);
}

Color Painter::getPaintColor()
{
    return *drawColor;
}

void Painter::setTextSize(int _textSize)
{
    textSize = _textSize;
}

void _swap_int16_t(int16_t& _first, int16_t& _second) 
{
	int16_t temp = _first;
	_first = _second;
	_second = temp;
}

void Painter::writePixel(int16_t _x, int16_t _y, uint16_t _color) 
{
    if ((_x >= 0) && (_x < DISPLAY_WIDTH) && (_y >= 0) && (_y < DISPLAY_HEIGHT)) 
    {
        buffer->setColor(_x + _y * DISPLAY_WIDTH, _color);
    }
}

void Painter::writeFillRect(int16_t _x, int16_t _y, 
	int16_t _width, int16_t _height, uint16_t _color) 
{
	if (_width && _height) // Nonzero width and height? 
	{
		if (_width < 0) // If negative width...
		{
			_x += _width + 1; //   Move X to left edge
			_width = -_width;     //   Use positive width
		}
		if (_x < DISPLAY_WIDTH) // Not off right
		{ 
			if (_height < 0) // If negative height...
			{
				_y += _height + 1;   //   Move Y to top edge
				_height = -_height;       //   Use positive height
			}
			if (_y < DISPLAY_HEIGHT) // Not off bottom
			{ 
				int16_t x2 = _x + _width - 1;
				if (x2 >= 0) // Not off left
				{ 
					int16_t y2 = _y + _height - 1;
					if (y2 >= 0) // Not off top
					{ 
						// Rectangle partly or fully overlaps screen
						if (_x < 0) 
						{
							_x = 0;
							_width = x2 + 1;
						} // Clip left
						if (_y < 0) 
						{
							_y = 0;
							_height = y2 + 1;
						} // Clip top
						if (x2 >= DISPLAY_WIDTH) 
						{
							_width = DISPLAY_WIDTH - _x;
						} // Clip right
						if (y2 >= DISPLAY_HEIGHT) 
						{
							_height = DISPLAY_HEIGHT - _y;
						} // Clip bottom
						for (int i = _y; i < _y + _height; i++)
						{
							for (int j = _x; j < _x + _width; j++)
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

void Painter::writeFastHLine(int16_t _x, int16_t _y, 
	int16_t _width, uint16_t _color) 
{
	// Y on screen, nonzero width
	if ((_y >= 0) && (_y < DISPLAY_HEIGHT) && _width)
	{ 
		if (_width < 0) // If negative width...
		{
			_x += _width + 1; //   Move X to left edge
			_width = -_width; //   Use positive width
		}
		if (_x < DISPLAY_WIDTH) // Not off right
		{ 
			int16_t x2 = _x + _width - 1;
			if (x2 >= 0) // Not off left
			{ 
				if (_x < 0) // Line partly or fully overlaps screen 
				{
					_x = 0;
					_width = x2 + 1;
				} // Clip left
				if (x2 >= DISPLAY_WIDTH) 
				{
					_width = DISPLAY_WIDTH - _x;
				} // Clip right
				for (int i = _y; i < _y + 1; i++)
				{
					for (int j = _x; j < _x + _width; j++)
					{
						buffer->setColor(j + i * DISPLAY_WIDTH, _color);
					}
				}
			}
		}
	}
}

void Painter::writeFastVLine(int16_t _x, int16_t _y, 
	int16_t _height, uint16_t _color) 
{
	// X on screen, nonzero height
	if ((_x >= 0) && (_x < DISPLAY_WIDTH) && _height) 
	{ 
		if (_height < 0) // If negative height... 
		{
			_y += _height + 1; //   Move Y to top edge
			_height = -_height; //   Use positive height
		}
		if (_y < DISPLAY_HEIGHT) // Not off bottom
		{ 
			int16_t y2 = _y + _height - 1;
			if (y2 >= 0) // Not off top
			{ 
				// Line partly or fully overlaps screen
				if (_y < 0) 
				{
					_y = 0;
					_height = y2 + 1;
				} // Clip top
				if (y2 >= DISPLAY_HEIGHT) 
				{
					_height = DISPLAY_HEIGHT - _y;
				} // Clip bottom
				for (int i = _y; i < _y + _height; i++)
				{
					for (int j = _x; j < _x + 1; j++)
					{
						buffer->setColor(j + i * DISPLAY_WIDTH, _color);
					}
				}
			}
		}
	}
}

void Painter::writeLine(int16_t _x0, int16_t _y0, 
	int16_t _x1, int16_t _y1, uint16_t _color) 
{
#if defined(ESP8266)
  	yield();
#endif
	int16_t steep = abs(_y1 - _y0) > abs(_x1 - _x0);
	if (steep) 
	{
		_swap_int16_t(_x0, _y0);
		_swap_int16_t(_x1, _y1);
	}

	if (_x0 > _x1) 
	{
		_swap_int16_t(_x0, _x1);
		_swap_int16_t(_y0, _y1);
	}

	int16_t dx, dy;
	dx = _x1 - _x0;
	dy = abs(_y1 - _y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (_y0 < _y1) 
	{
		ystep = 1;
	} 
	else 
	{
		ystep = -1;
	}

	for (; _x0 <= _x1; _x0++) 
	{
		if (steep) 
		{
			writePixel(_y0, _x0, _color);
		} else 
		{
			writePixel(_x0, _y0, _color);
		}
		err -= dy;
		if (err < 0) 
		{
			_y0 += ystep;
			err += dx;
		}
	}
}

void Painter::writeChar(int16_t _x, int16_t _y, 
	unsigned char _char, uint16_t _color, uint8_t _textSize) 
{
  	writeChar(_x, _y, _char, _color, _color, _textSize, _textSize);
}

void Painter::writeChar(int16_t _x, int16_t _y, 
	unsigned char _char, uint16_t _color, uint16_t _background, 
	uint8_t _sizeX, uint8_t _sizeY) 
{
	// Clip right, Clip bottom, Clip left, Clip top
    if (
		(_x >= DISPLAY_WIDTH) || (_y >= DISPLAY_HEIGHT) ||
        ((_x + 6 * _sizeX - 1) < 0) || ((_y + 8 * _sizeY - 1) < 0)
	)
	{
		return;	
	}

    for (int i = 0; i < 5; i++) // Char bitmap = 5 columns
	{ 
		uint8_t line = font[_char * 5 + i];
		for (int j = 0; j < 8; j++, line >>= 1) 
		{
			if (line & 1) 
			{
				if (_sizeX == 1 && _sizeY == 1) 
				{
					writePixel(_x + i, _y + j, _color);
				} 
				else 
				{
					writeFillRect(_x + i * _sizeX, _y + j * _sizeY, 
						_sizeX, _sizeY, _color);
				}
			} 
			// else if (_background != _color) 
			// {
			// 	if (_sizeX == 1 && _sizeY == 1) 
			// 	{
			// 		writePixel(_x + i, _y + j, _background);
			// 	}
			// 	else
			// 	{
			// 		writeFillRect(_x + i * _sizeX, _y + j * _sizeY, 
			// 			_sizeX, _sizeY, _background);
			// 	}
			// }
		}
    }
	// // If opaque, draw vertical line for last column
    // if (_background != _color) 
	// {
	// 	if (_sizeX == 1 && _sizeY == 1)
	// 	{
	// 		writeFastVLine(_x + 5, _y, 8, _background);
	// 	}
	// 	else
	// 	{
	// 		writeFillRect(_x + 5 * _sizeX, _y, _sizeX, 8 * _sizeY, _background);
	// 	}
    // }
}

void Painter::writeText(int16_t _x, int16_t _y, 
	std::string _text, uint16_t _color, uint8_t _size)
{
    std::string cyrilicText = fromCyrilic(_text);
    for (int i = 0; i < cyrilicText.size(); i++) 
	{
        painter->writeChar(_x + (i * ((5 * _size) + _size)), _y, 
			cyrilicText[i], _color, _size);
    }
}

std::string Painter::fromCyrilic(std::string _cyrilicString)
{
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
                    n = _cyrilicString[i]; 
                    i++;
                    if (n == 0x81) { n = 0xA9; break; }
                    if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
                    break;
                }
                case 0xD1: {
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

void Painter::drawBuffer()
{
    writeOpenGLBuffer();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Painter::writeOpenGLBuffer()
{
    float vertices[DISPLAY_WIDTH * DISPLAY_HEIGHT * 5];

    int verticesIndex = 0;
    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
        for (int j = 0; j < DISPLAY_WIDTH; j++)
        {
            uint16_t color(buffer->getColor(j + i * DISPLAY_WIDTH));
            Color rgbColor(color);
            vertices[verticesIndex * 5 + 0] = (float)j / (float)DISPLAY_WIDTH;
            vertices[verticesIndex * 5 + 1] = (float)i / (float)DISPLAY_HEIGHT;
            vertices[verticesIndex * 5 + 2] = (float)rgbColor.getR() / 255;
            vertices[verticesIndex * 5 + 3] = (float)rgbColor.getG() / 255;
            vertices[verticesIndex * 5 + 4] = (float)rgbColor.getB() / 255;
            verticesIndex++;
        }
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

void Painter::drawPixel(Point& _position) 
{
    writePixel(_position.getX(), _position.getY(), drawColor->toUint16());
}

void Painter::drawLine(Point& _position1, Point& _position2) 
{
	// Update in subclasses if desired!
	int16_t _x0 = _position1.getX();
	int16_t _y0 = _position1.getY();
	int16_t _x1 = _position2.getX();
	int16_t _y1 = _position2.getY();
	
	if (_x0 == _x1) 
	{
		if (y0 > y1) 
		{
			_swap_int16_t(_y0, _y1);
		}
		writeFastVLine(_x0, _y0, _y1 - _y0 + 1, drawColor->toUint16());
	} 
	else if (y0 == y1) 
	{
		if (_x0 > _x1)
		{
			_swap_int16_t(_x0, _x1);
		}
		writeFastHLine(_x0, _y0, _x1 - _x0 + 1, drawColor->toUint16());
	} 
	else 
	{
		writeLine(_x0, _y0, _x1, _y1, drawColor->toUint16());
	}
}

void Painter::drawLine(Point& _pointA, Point& _pointB, int _lineWidth)
{
    int offsetX, offsetY;
    if( _pointA.getY() == _pointB.getY() )
    {
        offsetX = 0;
        offsetY = 1;
    }
    else
    {
        offsetX = 1;
        offsetY = 0;
    }
    for(int i = 0; i < _lineWidth; i++)
    {
		Point position1(_pointA.getX() + (i * offsetX), 
			_pointA.getY() + (i * offsetY) );
		Point position2(_pointB.getX() + (i * offsetX), 
			_pointB.getY() + (i * offsetY));
        drawLine(position1, position2);
    }
}

void Painter::drawRect(Point& _position, Size& _size) 
{
    writeFillRect(_position.getX(), _position.getY(), 
		_size.getWidth(), _size.getHeight(), drawColor->toUint16());
}

void Painter::drawRect(Point& _position, Size& _size, Color& _color) 
{
    writeFillRect(_position.getX(), _position.getY(), 
		_size.getWidth(), _size.getHeight(), _color.toUint16());
}

void Painter::drawBorder(Point& _position, Size& _size) 
{
    writeFillRect(_position.getX(), _position.getY(), 
		_size.getWidth(), _size.getHeight(), drawColor->toUint16());
}

void Painter::drawBorder(Point& _position, Size& _size, Color& _color) 
{
    writeFillRect(_position.getX(), _position.getY(), 
		_size.getWidth(), _size.getHeight(), _color.toUint16());
}

void Painter::drawText(Point& _position, std::string& _text)
{
    writeText(_position.getX(), _position.getY(), 
		_text, drawColor->toUint16(), textSize);
}

void Painter::clearScreen(Color& _backgroundColor)
{
    writeFillRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 
		_backgroundColor.toUint16());
}

void Painter::testFont(int _fontPage)
{
    int gridSize = 16;
    int charOffset = 225 * _fontPage;
    for(int i = 0; i < gridSize; i++) 
	{
        for(int j = 0; j < gridSize; j++) 
		{
            // std::cout << charOffset +(gridSize*i+j) << " " 
			// 	<< char(charOffset +(gridSize*i+j)) << std::endl;
            writeChar(10 + i*6*1, 10 + j*8*1, char(charOffset +(gridSize*i+j)), 
				currentResourceTheme->getFocusColor().toUint16(), 1);
        }
    }
}

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
