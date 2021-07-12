#include "Line.h"
#include "Point.h"
#include "Size.h"
#include "DefinePainter.h"
#include "ResourceTheme.h"
#include "Color.h"
#include "VerticalLayout.h"

Line::Line() 
    : Widget(nullptr)
{
    //pointB( std::make_shared<Point>(_pointB)
}

Line::~Line()
{
}

void Line::render()
{
    painter->setPaintColor( painter->getResourceTheme()->getUnfocusColor() );
    Point pointB(widgetPosition->getX() + lineWidth, widgetPosition->getY());
    painter->paintLine(*widgetPosition, pointB, lineThickness);
}

int Line::getWidth()
{
    return lineWidth;
}

void Line::setWidth(int _lineWidth)
{
    lineWidth = _lineWidth;

    // int nextWidth = widgetSize->getWidth();
    // int nextHeight = widgetSize->getHeight();
    
    // int nextWidth = lineWidth > widgetSize->getWidth() ? lineWidth : widgetSize->getWidth();
    // nextHeight = lineThickness > nextHeight ? lineThickness : nextHeight;
    
    setSize( Size(lineWidth, lineThickness) );
    // pointA = std::make_shared<Point>(widgetPosition->getX(), widgetPosition->getY());
    // pointB = std::make_shared<Point>(widgetPosition->getX() + nextWidth, widgetPosition->getY());
    
    update();
    std::static_pointer_cast<VerticalLayout>(parentWidget)->countLayout();
}

int Line::getLineThickness()
{
    return lineWidth;
}

void Line::setLineThickness(int _lineThickness)
{
    lineThickness = _lineThickness;
    update();
}
