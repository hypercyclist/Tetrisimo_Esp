#include "Point.h"

Point::Point(int _x, int _y) : x(_x), y(_y)
{
}

Point::~Point()
{
}

int Point::getX()
{
    return x;
}

void Point::setX(int _x)
{
    x = _x;
}

int Point::getY()
{
    return y;
}

void Point::setY(int _y)
{
    y = _y;
}