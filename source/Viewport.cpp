#include "Point.h"
#include "Size.h"

Viewport::Viewport(Point _position, Size _size)
    : 
    position(std::make_shared<Point>(_position)),
    size(std::make_shared<Size>(_size))
{
}

Viewport::~Viewport()
{
}

Point Viewport::getPosition()
{
    return *position;
}

void Viewport::setPosition(Point _position)
{
    position = std::make_shared<Point>(_position);
}

Size Viewport::getSize()
{
    return *size;
}

void Viewport::setSize(Size _size)
{
    size = std::make_shared<Size>(_size);
}
