#include "Button.h"

#include "Color.h"
#include "Log.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"
#include "Viewport.h"

Button::Button(std::string _text) 
    : 
    Widget(),
    text(_text),
    textSize(2)
{
    focusability = true;
    processSizeUpdate();
}

Button::~Button()
{
}

void Button::render()
{
    if (focused)
    {
        painter->setPaintColor( painter->getResourceTheme()->getFocusColor() );
    }
    else
    {
        painter->setPaintColor( painter->getResourceTheme()->getUnfocusColor() );
    }
    painter->setTextSize(textSize);
    painter->drawText(*position, text);
}

void Button::processSizeUpdate()
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
    int nextWidth = size->getWidth();
    int nextHeight = size->getHeight();
    nextWidth = textWidth > nextWidth ? textWidth : nextWidth;
    nextHeight = textHeight > nextHeight ? textHeight : nextHeight;
    setSize( Size(nextWidth, nextHeight) );
}

std::string Button::getText()
{
    return text;
}

void Button::setText(std::string _text)
{
    text = _text;
    processSizeUpdate();
}

int Button::getTextSize()
{
    return textSize;
}

void Button::setTextSize(int _textSize)
{
    textSize = _textSize;
    processSizeUpdate();
}
