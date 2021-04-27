#include "Button.h"
#include "Size.h"
#include "Point.h"
#include "Painter.h"
#include "ResourceTheme.h"
#include "Color.h"

Button::Button(std::string _text) 
    : Widget(nullptr), 
    textSize(2)
{
    widgetPosition = std::make_unique<Point>(0, 0);
    widgetCanBeFocused = true;
    setText(_text);
}

Button::~Button()
{
}

void Button::render()
{
    if (widgetIsFocused)
    {
        painter->setDrawColor( painter->getResourceTheme()->getFocusColor() );
    }
    else
    {
        painter->setDrawColor( painter->getResourceTheme()->getUnfocusColor() );
    }
    painter->setTextSize(textSize);
    painter->drawText(text, *widgetPosition);
}

void Button::processSizeUpdate()
{
    std::string russianCharacters = "абвгдеёжзиклмнопрстуфхцчшщъыьэюя";
    int realStringLength = 0;
    for(int i = 0; i < text.length(); )
    {
        realStringLength += 1;
        bool isRussianCharacter = false;
        for(int j = 0; j < russianCharacters.length(); j++)
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
    int textWidth = 5 * textSize * realStringLength + ( realStringLength - 1) * textSize;
    int textHeight = 7 * textSize;
    int nextWidth = widgetSize->getWidth();
    int nextHeight = widgetSize->getHeight();
    nextWidth = textWidth > nextWidth ? textWidth : nextWidth;
    nextHeight = textHeight > nextHeight ? textHeight : nextHeight;
    setSize( Size(nextWidth, nextHeight) );
    update();
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
