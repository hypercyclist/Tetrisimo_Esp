#include "Label.h"

#include "Color.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"
#include "Viewport.h"

#include <iostream>

Label::Label(std::string _text)
    : 
    Widget(),
    text(_text), 
    textSize(2),
    underlined(false)
{
    processSizeUpdate();
}

Label::~Label()
{
}

void Label::render()
{
    // std::cout << "Label::render()" << std::endl;
    painter->setPaintColor( painter->getResourceTheme()->getUnfocusColor() );
    painter->setTextSize(textSize);
    // painter->drawText(position->getX(), position->getY(), text, painter->getResourceTheme()->getFocusColor().toUint16(), textSize);
    painter->drawText(*position, text);
    if (underlined)
    {
        // int lineThickness = textSize == 3 ? 2 : 1;
        int lineThickness = 2;
        
        Point pointA(position->getX(), 
            position->getY() + size->getHeight() - 1);

        Point pointB(position->getX() + size->getWidth(),
             position->getY() + size->getHeight() - 1);
        
        painter->drawLine(pointA, pointB, lineThickness);
    }
}

void Label::render(std::shared_ptr<Viewport> _viewport)
{
    Point offsetPosition(
        position->getX() - _viewport->getPosition().getX(), 
        position->getY() - _viewport->getPosition().getY()
    );
    // std::cout << "Label::render()" << std::endl;
    painter->setPaintColor( painter->getResourceTheme()->getUnfocusColor() );
    painter->setTextSize(textSize);
    // painter->drawText(offsetPosition.getX(), offsetPosition.getY(), text, painter->getResourceTheme()->getFocusColor().toUint16(), textSize);
    painter->drawText(*position, text);
    if (underlined)
    {
        // int lineThickness = textSize == 3 ? 2 : 1;
        int lineThickness = 2;
        
        Point pointA(offsetPosition.getX(), 
            offsetPosition.getY() + size->getHeight() - 1);

        Point pointB(offsetPosition.getX() + size->getWidth(),
             offsetPosition.getY() + size->getHeight() - 1);
        
        painter->drawLine(pointA, pointB, lineThickness);
    }
}

void Label::processSizeUpdate()
{
    std::string russianCharacters = "абвгдеёжзиклмнопрстуфхцчшщъыьэюя";
    int realStringLength = 0;
    for (int i = 0; i < text.length(); )
    {
        realStringLength += 1;
        bool isRussianCharacter = false;
        for (int j = 0; j < russianCharacters.length(); j++)
        {
            if (text[i] == russianCharacters[j])
            {
                isRussianCharacter = true;
                break;
            }
        }
        int increment = isRussianCharacter ? 2 : 1;
        i += increment;
    }
    int textWidth = 5 * textSize * realStringLength 
        + ( realStringLength - 1) * textSize;
    int textHeight = 7 * textSize;
    if (underlined)
    {
        textHeight = textSize == 3 ? textHeight + 4 : textHeight + 3;
    }
    int nextWidth = size->getWidth();
    int nextHeight = size->getHeight();
    nextWidth = textWidth > nextWidth ? textWidth : nextWidth;
    nextHeight = textHeight > nextHeight ? textHeight : nextHeight;
    setSize( Size(nextWidth, nextHeight) );
}

std::string Label::getText()
{
    return text;
}

void Label::setText(std::string _text)
{
    text = _text;
    processSizeUpdate();
}

int Label::getTextSize()
{
    return textSize;
}

void Label::setTextSize(int _textSize)
{
    textSize = _textSize;
    processSizeUpdate();
}

bool Label::isUnderlined()
{
    return underlined;
}

void Label::setUnderline(bool _underline)
{
    underlined = _underline;
    processSizeUpdate();
}
