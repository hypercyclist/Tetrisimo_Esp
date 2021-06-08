#include "CheckBox.h"
#include "Painter.h"
#include "Color.h"
#include "ResourceTheme.h"
#include "Point.h"
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
        painter->setDrawColor( painter->getResourceTheme()->getFocusColor() );
    }
    else
    {
        painter->setDrawColor( painter->getResourceTheme()->getUnfocusColor() );
    }
    painter->setTextSize(textSize);
    painter->drawText(text, *position);

    int x = position->getX() + size->getWidth() - size->getHeight();
    int y = position->getY();
    int checkBoxSize = size->getHeight();
    uint16_t focusColor = painter->getDrawColor().toUint16();
    uint16_t bacgroundColor = painter->getResourceTheme()->getBackgroundMenuColor().toUint16();
    painter->drawRect(x, y, checkBoxSize, checkBoxSize, focusColor);
    painter->drawRect(x + 1, y + 1, checkBoxSize - 2, checkBoxSize - 2, focusColor);
    painter->fillRect(x + 2, y + 2, checkBoxSize - 4, checkBoxSize - 4, bacgroundColor);

    painter->setDrawColor(painter->getResourceTheme()->getFocusColor());
    if(state)
    {
        painter->drawLine(x + 2, y + 7, x + 5, y + 11);
        painter->drawLine(x + 3, y + 7, x + 6, y + 11);
        painter->drawLine(x + 4, y + 7, x + 7, y + 11);
        painter->drawLine(x + 7, y + 11, x + 10, y + 2);
        painter->drawLine(x + 8, y + 11, x + 11, y + 2);
    }
    else
    {
        painter->drawLine(x + 2, y + 2, x + 10, y + 11);
        painter->drawLine(x + 2, y + 3, x + 10, y + 11);
        painter->drawLine(x + 2, y + 2, x + 11, y + 11);
        painter->drawLine(x + 10, y + 2, x + 2, y + 11);
        painter->drawLine(x + 11, y + 2, x + 3, y + 11);
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
        Serial.println(nextWidth);
        nextHeight = size->getHeight();
        update();
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

void CheckBox::update()
{
    Serial.println("CheckBox::update()");
    needUpdate = true;
    if (parent != nullptr)
    {
        parent->update();
    }
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
