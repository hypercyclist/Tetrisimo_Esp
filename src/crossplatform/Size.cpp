#include "Size.h"

Size::Size() 
    : width(0), height(0)
{
}

Size::Size(int _width, int _height) 
    : width(_width), height(_height)
{
}

void Size::setSize(int _width, int _height)
{
    width = _width;
    height = _height;
}

void Size::setWidth(int _width)
{
    width = _width;
}

int Size::getWidth() const
{
    return width;
}

void Size::setHeight(int _height)
{
    height = _height;
}

int Size::getHeight() const
{
    return height;
}

// Size Size::operator=(Size _size)
// {
//     return _size;
// }

bool Size::operator==(const Size& foo)
{
    return width == foo.getWidth() && height == foo.getHeight()
    ? true : false;
}

bool Size::operator!=(const Size& foo)
{
    return width != foo.getWidth() || height != foo.getHeight()
    ? true : false;
}
