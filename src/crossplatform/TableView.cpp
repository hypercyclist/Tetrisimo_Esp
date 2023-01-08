#include "TableView.h"

#include "Color.h"
#include "Log.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"
#include "StringUtf.h"

TableView::TableView(std::string _name) 
    : 
    Widget(),
    name(_name),
    textSize(1),
    wrapSize(name.length()) // Bad.
{
    focusability = true;
    processSizeUpdate();
    setExecuteFunction([this] () { });
}

TableView::~TableView()
{
}

void TableView::setParent(std::shared_ptr<Widget> _parent)
{
    parent = _parent;
    processSizeUpdate();
    // processParent();
}

void TableView::render()
{
    // Widget height is table header + separator + body.
    // Header is 3px border + textHeight + 3px border.
    // Body is textHeight + 1px separator * lines count.
    int x = position->getX();
    int y = position->getY();
    int border = 3;
    Size textSpace = painter->countTextSize(name, textSize);
    int separator = 1;
    int lines = getLinesCount() > 0 ? getLinesCount() : 1;
    lines = (lines > 3) && (!maximized) ? 3 : lines;
    int nameX = x + (size->getWidth() - textSpace.getWidth()) / 2;
    int nameY = y + border + separator;
    int textX = x + 4;
    int textY = y + ( border * 2) + textSpace.getHeight() + separator * 3;
    Color focusColor = painter->getPaintColor();
    Color backgroundColor = 
        painter->getResourceTheme()->getBackgroundMenuColor();
    Color outBorderColor = 
        painter->getResourceTheme()->getBackgroundGameColor();
    Color middleBorderColor = focused ?
        painter->getResourceTheme()->getFocusColor() :
        painter->getResourceTheme()->getBorderColor();

    // Draw table: background, 2px border, 
    // border around name, border arount text, separator border.
    painter->drawRect(*position, *size, backgroundColor);
    
    painter->drawBorder(*position, *size, outBorderColor);

    Point position_1(x + 1, y + 1);
    Size size_1(getWidth() - 2, getHeight() - 2);
    painter->drawBorder(position_1, size_1, middleBorderColor);

    Point position_2(x + 2, y + 2);
    Size size_2(getWidth() - 4, separator * 2 + textSpace.getHeight() + 2);
    painter->drawBorder(position_2, size_2, outBorderColor);
    
    Point position_3(x + 2, y + ( border * 2) + textSpace.getHeight() + 1);
    Size size_3(getWidth() - 4, (textSpace.getHeight() + separator) * 
        lines + separator + 2);
    painter->drawBorder(position_3, size_3, outBorderColor);

    painter->setPaintColor(middleBorderColor);
    painter->drawLine(Point(x + 1, y + ( border * 2) + textSpace.getHeight()), 
        Point(x + 1 + getWidth() - 2, y + ( border * 2) + textSpace.getHeight()));

    // Draw name and text.
    painter->setPaintColor( painter->getResourceTheme()->getUnfocusColor() );
    painter->setTextSize(1);
    Point namePosition(nameX, nameY);
    painter->drawText(namePosition, name);

    // painter->setPaintColor( painter->getResourceTheme()->getFocusColor() );
    for(int i = 0; i < lines; i++)
    {
        Point textPosition(textX, textY);
        painter->drawText(textPosition, text[i]);
        textY += textSpace.getHeight() + separator;
    }
}

void TableView::processSizeUpdate()
{
    // Widget height is table header + separator + body.
    // Header is 3px border + textHeight + 3px border.
    // Body is textHeight + 1px separator * lines count.

    // Count widget width.
    Size countedSize;
    if (parent != nullptr)
    {
        Size layoutSize = parent->getSize();
        countedSize = painter->countTextSize(name, textSize);
        countedSize.setWidth( layoutSize.getWidth() * 0.87f );
    }
    else
    {
        countedSize = painter->countTextSize(name, textSize);
        for (int i = 0; i < getLinesCount(); i++)
        {
            countedSize = countedSize.getWidth() > 
                painter->countTextSize(text[i], textSize).getWidth()
            ? countedSize : painter->countTextSize(text[i], textSize);
        }
    }

    // Count text array.
    wrapSize = painter->countWrapSize(textSize, countedSize.getWidth());

    // Count widget height.
    int border = 3;
    int textHeight = countedSize.getHeight();
    int separator = 1;
    int lines = getLinesCount() > 0 ? getLinesCount() : 1;
    lines = (lines > 3) && (!maximized) ? 3 : lines;
    countedSize.setHeight(
        textHeight + (border * 2) + 
        (separator * 2) + 
        ((textHeight + separator) * lines) + 
        separator + border
    );
    setSize(countedSize);
}

void TableView::setName(std::string _name)
{
    name = _name;
    processSizeUpdate();
}

std::string TableView::getName()
{
    return name;
}

void TableView::addText(std::string _text)
{
    text.push_back(_text);
    processSizeUpdate();
}

void TableView::removeText(int _index)
{
    text.erase(std::next(text.begin(), _index));
    processSizeUpdate();
}

std::string TableView::getText(int _index)
{
    return text[_index];
}

int TableView::getTextSize()
{
    return textSize;
}

void TableView::setTextSize(int _textSize)
{
    textSize = _textSize;
    processSizeUpdate();
}

int TableView::getLinesCount()
{
    return text.size();
}
