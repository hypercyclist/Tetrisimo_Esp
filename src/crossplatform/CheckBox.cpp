#include "CheckBox.h"

#include "Color.h"
#include "Log.h"
#include "Painter.h"
#include "Point.h"
#include "ResourceTheme.h"
#include "Size.h"

CheckBox::CheckBox(std::string _text, bool _state) 
    : 
    Widget(),
    text(_text),
    textSize(2),
    state(_state)
{
    focusability = true;
    processSizeUpdate();
}

CheckBox::CheckBox()
    : 
    Widget(),
    text(""),
    textSize(2),
    state(false)
{
    focusability = false;
    processSizeUpdate();
}

CheckBox::~CheckBox()
{
}

void CheckBox::setParent(std::shared_ptr<Widget> _parent)
{
    parent = _parent;
    processSizeUpdate();
    // processParent();
}

void CheckBox::render()
{
    // processSizeUpdate();
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

    int x = position->getX() + size->getWidth() - size->getHeight();
    int y = position->getY();
    Color focusColor = painter->getPaintColor();
    Color backgroundColor = painter->getResourceTheme()->getBackgroundMenuColor();

    painter->drawBorder(*position, *size, focusColor);
    
    Point position_1(x + 1, y + 1);
    Size size_1(getWidth() - 2, getHeight() - 2);
    painter->drawBorder(position_1, size_1, focusColor);
    
    Point position_2(x + 2, y + 2);
    Size size_2(getWidth() - 4, getHeight() - 4);
    painter->drawBorder(position_1, size_1, backgroundColor);

    painter->setPaintColor(painter->getResourceTheme()->getFocusColor());
    if(state)
    {
        // painter->paintLine(x + 2, y + 7, x + 5, y + 11);
        // painter->paintLine(x + 3, y + 7, x + 6, y + 11);
        // painter->paintLine(x + 4, y + 7, x + 7, y + 11);
        // painter->paintLine(x + 7, y + 11, x + 10, y + 2);
        // painter->paintLine(x + 8, y + 11, x + 11, y + 2);
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
