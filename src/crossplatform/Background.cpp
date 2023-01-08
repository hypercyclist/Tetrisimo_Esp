#include "Background.h"

#include "Color.h"
#include "Log.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"

#include <memory>
#include <iostream>

Background::Background() : 
    Widget()
{
}

Background::~Background()
{
}

void Background::render()
{
    drawNet();
}

void Background::drawNet()
{
    Color backgroundColor = painter->getResourceTheme()->getBackgroundMenuColor();
    Color netColor = painter->getResourceTheme()->getNetColor();
    painter->clearScreen( backgroundColor );
    painter->setPaintColor( netColor );

    for (int i = size->getWidth(); i >= 0; i -= 8)
    {
        Point position1(i, 0);
        Point position2(i, size->getHeight());
        painter->drawLine(position1, position2);
    }
    for (int i = -1; i < size->getHeight(); i += 8)
    {
        Point position1(0, i);
        Point position2(size->getWidth(), i);
        painter->drawLine(position1, position2);
    }
}
