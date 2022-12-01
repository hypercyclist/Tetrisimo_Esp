#include "Background.h"

#include "Color.h"
#include "Log.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"

#include <memory>
#include <iostream>

Background::Background() 
    : 
    Widget()
{
}

Background::~Background()
{
}



void Background::render()
{
    Log::println("Background::render()", "LOW");
    drawNet();
}

void Background::drawNet()
{
    Color backgroundColor = painter->getResourceTheme()->getBackgroundMenuColor();
    std::cout << backgroundColor.getR() << " " 
            << backgroundColor.getG()  << " "
            << backgroundColor.getB() << std::endl;
    Color netColor = painter->getResourceTheme()->getNetColor();
    painter->background( backgroundColor );
    painter->setPaintColor( netColor );

    for (int i = size->getWidth(); i >= 0; i -= 8)
    {
        // painter->drawLine( Point(i, 0), Point(i, size->getHeight()) );
        painter->drawFastVLine(i, 0, size->getHeight(), netColor.toUint16());
    }
    for (int i = -1; i < size->getHeight(); i += 8)
    {
        // painter->paintLine( Point(size->getWidth(), i), Point(0, i) );
        painter->drawFastHLine(0, i, size->getWidth(), netColor.toUint16());
    }
    painter->drawChar(10, 10, 'H', painter->getResourceTheme()->getFocusColor().toUint16(), painter->getResourceTheme()->getFocusColor().toUint16(), 3, 3);
    painter->drawChar(30, 10, 'E', painter->getResourceTheme()->getFocusColor().toUint16(), painter->getResourceTheme()->getFocusColor().toUint16(), 3, 3);
    painter->drawChar(50, 10, 'L', painter->getResourceTheme()->getFocusColor().toUint16(), painter->getResourceTheme()->getFocusColor().toUint16(), 3, 3);
    painter->drawChar(70, 10, 'L', painter->getResourceTheme()->getFocusColor().toUint16(), painter->getResourceTheme()->getFocusColor().toUint16(), 3, 3);
    painter->drawChar(90, 10, 'O', painter->getResourceTheme()->getFocusColor().toUint16(), painter->getResourceTheme()->getFocusColor().toUint16(), 3, 3);
}
