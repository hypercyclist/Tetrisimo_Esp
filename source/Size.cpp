#include "Size.h"

// Size::Size() 
//     : width(0), height(0)
// {
// }

Size::Size(int _width, int _height) 
    : width(_width), height(_height)
{
}

// Size Size::operator=(Size _size)
// {
//     return _size;
// }

void Size::setSize(int _width, int _height)
{
    width = _width;
    height = _height;
}

void Size::setWidth(int _width)
{
    width = _width;
}

int Size::getWidth()
{
    return width;
}

void Size::setHeight(int _height)
{
    height = _height;
}

int Size::getHeight()
{
    return height;
}