#include "CheckBox.h"
#include "Painter.h"
#include "Color.h"
#include "ResourceTheme.h"
#include "Point.h"
#include "Size.h"

CheckBox::CheckBox(std::string _text) 
    : 
    Widget(),
    text(_text),
    textSize(2)
{
    focusability = true;
    processSizeUpdate();
}

CheckBox::CheckBox()
    : 
    Widget(),
    text(""),
    textSize(2)
{
    focusability = false;
    processSizeUpdate();
}

CheckBox::~CheckBox()
{
}



void CheckBox::render()
{
    processSizeUpdate();
    if (focused)
    {
        painter->setDrawColor( painter->getResourceTheme()->getFocusColor() );
    }
    else
    {
        painter->setDrawColor( painter->getResourceTheme()->getUnfocusColor() );
    }
    painter->setTextSize(textSize);
    painter->drawText(text, *position);

    // painter->drawLine(pointA, pointB, lineThickness);
}

void CheckBox::processSizeUpdate()
{
    int nextWidth;
    int nextHeight;
    if (parent != nullptr)
    {
        Size layoutSize = parent->getSize();
        nextWidth = layoutSize.getWidth() * 0.90f;
        nextHeight = size->getHeight();
        Serial.println("parent != nullptr ");
        // Serial.println(text.c_str());
    }
    else
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
        nextWidth = size->getWidth();
        nextHeight = size->getHeight();
        nextWidth = textWidth > nextWidth ? textWidth : nextWidth;
        nextHeight = textHeight > nextHeight ? textHeight : nextHeight;
        // Serial.println("parent == nullptr ");
        // Serial.println(text.c_str());
    }
    // Serial.println(nextWidth);
    setSize( Size(nextWidth, nextHeight) );
}



std::string CheckBox::getText()
{
    return text;
}

void CheckBox::setText(std::string _text)
{
    text = _text;
    processSizeUpdate();
}

int CheckBox::getTextSize()
{
    return textSize;
}

void CheckBox::setTextSize(int _textSize)
{
    textSize = _textSize;
    processSizeUpdate();
}
