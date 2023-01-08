#include "CheckBox.h"

#include "Color.h"
#include "Log.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"

CheckBox::CheckBox(std::string _text, bool _state) :
    Widget(),
    text(_text),
    textSize(2),
    state(_state)
{
    focusability = true;
    processSizeUpdate();
}

CheckBox::CheckBox() : 
    Widget(),
    text(""),
    textSize(2),
    state(false)
{
    focusability = false;
    processSizeUpdate();
}

CheckBox::~CheckBox() { }

void CheckBox::setParent(std::shared_ptr<Widget> _parent)
{
    parent = _parent;
    processSizeUpdate();
    // processParent();
}

void CheckBox::render()
{
    Color textColor = focused ? painter->getResourceTheme()->getFocusColor() :
        painter->getResourceTheme()->getUnfocusColor();
    painter->setTextSize(textSize);
    painter->drawText(*position, text, textColor);

    int x = position->getX() + size->getWidth() - size->getHeight();
    int y = position->getY();

    Color focusColor = painter->getResourceTheme()->getFocusColor();
    Color backgroundColor = painter->getResourceTheme()->getBackgroundMenuColor();
    Color borderColor1 = painter->getResourceTheme()->getNetColor();
    Color borderColor2 = focused ? painter->getResourceTheme()->getFocusColor() :
        painter->getResourceTheme()->getBorderColor();

    painter->drawRect(Point(x, y), 
        Size(getHeight(), getHeight()), backgroundColor);
    painter->drawBorder(Point(x, y), 
        Size(getHeight(), getHeight()), borderColor1);
    
    painter->drawBorder(Point (x + 1, y + 1), 
        Size(getHeight() - 2, getHeight() - 2), borderColor2);

    painter->drawBorder(Point (x + 2, y + 2), 
        Size(getHeight() - 4, getHeight() - 4), borderColor1);
    
    painter->setPaintColor(focusColor);
    if(state)
    {
        painter->drawLine(Point(x + 2, y + 7), Point(x + 5, y + 11));
        painter->drawLine(Point(x + 3, y + 7), Point(x + 6, y + 11));
        painter->drawLine(Point(x + 4, y + 7), Point(x + 7, y + 11));
        painter->drawLine(Point(x + 7, y + 11), Point(x + 10, y + 2));
        painter->drawLine(Point(x + 8, y + 11), Point(x + 11, y + 2));
    }
}

void CheckBox::processSizeUpdate()
{
    int nextWidth;
    int nextHeight;
    if (parent != nullptr)
    {
        Size layoutSize = parent->getSize();
        nextWidth = layoutSize.getWidth() * 0.74f;
        Log::println(nextWidth, "LOW");
        nextHeight = size->getHeight();
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

int CheckBox::getState()
{
    return state;
}

void CheckBox::setState(int _state)
{
    state = _state;
}
