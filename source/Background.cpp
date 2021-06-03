#include "Background.h"
#include "Painter.h"
#include "Color.h"
#include "ResourceTheme.h"
#include "Point.h"
#include "Size.h"

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
    drawNet();
}

void Background::drawNet()
{
    std::shared_ptr<ResourceTheme> theme = painter->getResourceTheme();
    painter->background( theme->getBackgroundMenuColor() );
    painter->setDrawColor( theme->getNetColor() );
    
    for (int i = size->getWidth(); i >= 0; i -= 8)
    {
        painter->drawLine( Point(i, 0), Point(i, size->getHeight()) );
    }
    for (int i = -1; i < size->getHeight(); i += 8)
    {
        painter->drawLine( Point(size->getWidth(), i), Point(0, i) );
    }
}
