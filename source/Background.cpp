#include "Background.h"
#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "Painter.h"
#include "ResourceTheme.h"

Background::Background(std::shared_ptr<Widget> _parentWidget) : Widget(_parentWidget)
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
    // tft->setRotation(0);
    // tft->background(80, 80, 80);
    // tft->setRotation(1);
    // tft->setPenColor(0, 0, 0);
    for (int i = widgetSize->getWidth(); i >= 0; i -= 8)
    {
        painter->drawLine( Point(i, 0), Point(i, widgetSize->getHeight()) );
    }
    for (int i = -1; i < widgetSize->getHeight(); i += 8)
    {
        painter->drawLine( Point(widgetSize->getWidth(), i), Point(0, i) );
    }
}
