#include "PaletteView.h"

#include "Color.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"

PaletteView::PaletteView() 
    : 
    Widget()
{
    processSizeUpdate();
}

PaletteView::~PaletteView()
{
}

void PaletteView::setParent(std::shared_ptr<Widget> _parent)
{
    parent = _parent;
    processSizeUpdate();
}

void PaletteView::render()
{
    int x = position->getX();
    int y = position->getY();
    int border = 2;
    int netSize = 7;
    int netWidth = 12;
    int netHeight = 5;
    Color focusColor = painter->getPaintColor();
    Color bacgroundColor = 
        painter->getResourceTheme()->getBackgroundMenuColor();
    Color outBorderColor = 
        painter->getResourceTheme()->getBackgroundGameColor();
    Color middleBorderColor = focused ?
        painter->getResourceTheme()->getFocusColor() :
        painter->getResourceTheme()->getBorderColor();
    Color netColor = painter->getResourceTheme()->getNetColor();

    // Draw table: background, 2px border, 
    // border around name, border arount text, separator border.
    painter->paintRect(x, y, getWidth(), getHeight(), bacgroundColor);
    painter->paintBorder(x, y, getWidth(), getHeight(), outBorderColor);
    painter->paintBorder(
        x + 1, 
        y + 1, 
        getWidth() - 2, 
        getHeight() - 2, 
        middleBorderColor);

    // painter->paintBorder(
    //     x + 2, 
    //     y + 2, 
    //     getWidth() - 4, 
    //     getHeight() - 4, 
    //     outBorderColor);

    painter->setPaintColor(netColor);
    for (int i = x + border; i < x + getWidth() - border - 1; i+= netSize + 1)
    {
        painter->paintLine( Point(i, y + border), Point(i, y + getHeight() - border - 1) );
    }
    for (int i = y + border; i < y + getHeight() - border -1; i+= netSize + 1)
    {
        painter->paintLine( Point(x + border, i), Point(x + getWidth() - border, i) );
    }
}

void PaletteView::processSizeUpdate()
{
    // Count widget width.
    int border = 2;
    int netSize = 7;
    int netWidth = 12;
    int netHeight = 5;
    Size countedSize;
    countedSize.setWidth( (netWidth * netSize) + (netWidth - 1) + (border * 2) );
    countedSize.setHeight( (netHeight * netSize) + (netHeight - 1) + (border * 2) );
    if (*size != countedSize)
    {
        update();
    }
    setSize(countedSize);
}

void PaletteView::update()
{
    Serial.println("PaletteView::update()");
    needUpdate = true;
    if (parent != nullptr)
    {
        parent->update();
    }
}
