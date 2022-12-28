#include "PaletteView.h"

#include "Color.h"
#include "Log.h"
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
    Color backgroundColor = 
        painter->getResourceTheme()->getBackgroundMenuColor();
    Color outBorderColor = 
        painter->getResourceTheme()->getBackgroundGameColor();
    Color middleBorderColor = focused ?
        painter->getResourceTheme()->getFocusColor() :
        painter->getResourceTheme()->getBorderColor();
    Color netColor = painter->getResourceTheme()->getNetColor();

    // Draw table: background, 2px border, 
    // border around name, border arount text, separator border.
    painter->drawRect(*position, *size, backgroundColor);
    painter->drawBorder(*position, *size, outBorderColor);
    Point position_1(x + 1, y + 1);
    Size size_1(getWidth() - 2, getHeight() - 2);
    painter->drawBorder(position_1, size_1, middleBorderColor);

    // painter->paintBorder(
    //     x + 2, 
    //     y + 2, 
    //     getWidth() - 4, 
    //     getHeight() - 4, 
    //     outBorderColor);

    painter->setPaintColor(netColor);
    for (int i = x + border; i < x + getWidth() - border; i+= netSize + 1)
    {
        // painter->paintLine( Point(i, y + border), Point(i, y + getHeight() - border - 1) );
    }
    for (int i = y + border; i < y + getHeight() - border; i+= netSize + 1)
    {
        // painter->paintLine( Point(x + border, i), Point(x + getWidth() - border - 1, i) );
    }
    Color figureIColor = painter->getResourceTheme()->getFigureIColor();
    Color figureJColor = painter->getResourceTheme()->getFigureJColor();
    Color figureLColor = painter->getResourceTheme()->getFigureLColor();
    Color figureOColor = painter->getResourceTheme()->getFigureOColor();
    Color figureSColor = painter->getResourceTheme()->getFigureSColor();
    Color figureTColor = painter->getResourceTheme()->getFigureTColor();
    Color figureZColor = painter->getResourceTheme()->getFigureZColor();
    // Figure L.
    paintBlock(0, 2, figureLColor);
    paintBlock(0, 3, figureLColor);
    paintBlock(0, 4, figureLColor);
    paintBlock(1, 4, figureLColor);
    // Figure O.
    paintBlock(2, 3, figureOColor);
    paintBlock(2, 4, figureOColor);
    paintBlock(3, 3, figureOColor);
    paintBlock(3, 4, figureOColor);
    // Figure T.
    paintBlock(4, 4, figureTColor);
    paintBlock(5, 3, figureTColor);
    paintBlock(5, 4, figureTColor);
    paintBlock(6, 4, figureTColor);
    // Figure Z.
    paintBlock(5, 2, figureZColor);
    paintBlock(6, 2, figureZColor);
    paintBlock(6, 3, figureZColor);
    paintBlock(7, 3, figureZColor);
    // Figure S.
    paintBlock(7, 4, figureSColor);
    paintBlock(8, 4, figureSColor);
    paintBlock(8, 3, figureSColor);
    paintBlock(9, 3, figureSColor);
    // Figure J.
    paintBlock(9, 4, figureJColor);
    paintBlock(10, 4, figureJColor);
    paintBlock(10, 3, figureJColor);
    paintBlock(10, 2, figureJColor);
    // Figure I.
    paintBlock(11, 4, figureIColor);
    paintBlock(11, 3, figureIColor);
    paintBlock(11, 2, figureIColor);
    paintBlock(11, 1, figureIColor);

}

void PaletteView::processSizeUpdate()
{
    // Count widget width.
    int border = 2;
    int netSize = 7;
    int netWidth = 12;
    int netHeight = 5;
    Size countedSize;
    countedSize.setWidth( (netWidth * netSize) + (netWidth + 1) + (border * 2) );
    countedSize.setHeight( (netHeight * netSize) + (netHeight + 1) + (border * 2) );
    setSize(countedSize);
}

void PaletteView::paintBlock(int _x, int _y, Color _color)
{
    int border = 3;
    int netSize = 7;
    int x = position->getX();
    int y = position->getY();
    Point realPosition(x + (_x * (netSize + 1)) + border,
        y + (_y * (netSize + 1)) + border);
    Size blockSize(netSize, netSize);
    painter->drawRect(realPosition, blockSize, _color);
    Color borderColor(_color.getR() - 10, _color.getG() - 10, _color.getB() - 10);
    painter->drawBorder(realPosition, blockSize, borderColor);
}
