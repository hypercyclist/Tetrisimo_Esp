#include "TextView.h"

#include "Color.h"
#include "Log.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"
#include "StringUtf.h"

TextView::TextView(std::string _name, std::string _text) 
    : 
    Widget(),
    name(_name),
    textOriginal(_text),
    textSize(1),
    wrapSize(name.length()) // Bad.
{
    focusability = true;
    processSizeUpdate();
}

TextView::~TextView()
{
}

void TextView::setParent(std::shared_ptr<Widget> _parent)
{
    parent = _parent;
    processSizeUpdate();
    // processParent();
}

void TextView::render()
{
    // Widget height is table header + separator + body.
    // Header is 3px border + textHeight + 3px border.
    // Body is textHeight + 1px separator * lines count.
    int x = position->getX();
    int y = position->getY();
    int border = 3;
    Size textSpace = painter->countTextSize(name, textSize);
    int separator = 1;
    int nameX = x + (size->getWidth() - textSpace.getWidth()) / 2;
    int nameY = y + border + separator;
    int textX = x + 4;
    int textY = y + ( border * 2) + textSpace.getHeight() + separator * 3;
    Color focusColor = painter->getPaintColor();
    Color bacgroundColor = 
        painter->getResourceTheme()->getBackgroundMenuColor();
    Color outBorderColor = 
        painter->getResourceTheme()->getBackgroundGameColor();
    Color middleBorderColor = focused ?
        painter->getResourceTheme()->getFocusColor() :
        painter->getResourceTheme()->getBorderColor();

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

    painter->paintBorder(
        x + 2, 
        y + 2, 
        getWidth() - 4, 
        separator * 2 + textSpace.getHeight() + 2, 
        outBorderColor);
    
    painter->paintBorder(
        x + 2, 
        y + ( border * 2) + textSpace.getHeight() + 1, 
        getWidth() - 4, 
        (textSpace.getHeight() + separator) * getLinesCount() + separator + 2, 
        outBorderColor);

    painter->setPaintColor(middleBorderColor);
    // painter->paintLine(
    //     x + 1, 
    //     y + ( border * 2) + textSpace.getHeight(), 
    //     x + getWidth() - 2, 
    //     y + ( border * 2) + textSpace.getHeight());

    // Draw name and text.
    painter->setPaintColor( painter->getResourceTheme()->getUnfocusColor() );
    painter->setTextSize(textSize);
    painter->drawText(Point(nameX, nameY), name);

    for(int i = 0; i < text.size(); i++)
    {
        painter->drawText(Point(textX, textY), text[i]);
        textY += textSpace.getHeight() + separator;
    }
}

void TextView::processSizeUpdate()
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
    setText(textOriginal);

    // Count widget height.
    int border = 3;
    int textHeight = countedSize.getHeight();
    int separator = 1;
    int lines = getLinesCount() > 0 ? getLinesCount() : 1;
    countedSize.setHeight(
        textHeight + (border * 2) + 
        (separator * 2) + 
        ((textHeight + separator) * lines) + 
        separator + border
    );
    setSize(countedSize);
}

void TextView::setName(std::string _name)
{
    name = _name;
    processSizeUpdate();
}

std::string TextView::getName()
{
    return name;
}

void TextView::setText(std::string _text)
{
    textOriginal = _text;
    int tempSizeCount = StringUtf::length(textOriginal) / wrapSize;
    tempSizeCount = (float)tempSizeCount < 
        (float)StringUtf::length(textOriginal) / (float)wrapSize ? 
        tempSizeCount + 1 : tempSizeCount;
    tempSizeCount = tempSizeCount == 0 ? 1 : tempSizeCount;
    text.resize(tempSizeCount);
    for(int i = 0; i < text.size() - 1; i++)
    {
        text[i] = StringUtf::substr(textOriginal, wrapSize * i, wrapSize);
    }
    text[text.size() - 1] = StringUtf::substr(_text, wrapSize * (text.size() - 1));
}

std::string TextView::getText()
{
    return textOriginal;
}

int TextView::getTextSize()
{
    return textSize;
}

void TextView::setTextSize(int _textSize)
{
    textSize = _textSize;
    processSizeUpdate();
}

int TextView::getLinesCount()
{
    return text.size();
}
