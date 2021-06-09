#include "TableView.h"
#include "Painter.h"
#include "Color.h"
#include "ResourceTheme.h"
#include "Point.h"
#include "Size.h"

TableView::TableView(std::string _text) 
    : 
    Widget(),
    text(_text),
    textSize(1)
{
    focusability = true;
    processSizeUpdate();
}

TableView::TableView()
    : 
    Widget(),
    text(""),
    textSize(1)
{
    focusability = true;
    processSizeUpdate();
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
    // painter->drawRect(x, y, checkBoxSize, checkBoxSize, focusColor);
    // painter->drawRect(x + 1, y + 1, checkBoxSize - 2, checkBoxSize - 2, focusColor);
    // painter->fillRect(x + 2, y + 2, checkBoxSize - 4, checkBoxSize - 4, bacgroundColor);

    painter->fillRect(x, y, getWidth(), getHeight, bacgroundColor);
    painter->drawRect(x, y, getWidth(), getHeight, bacgroundColor);
    // painter->drawRect(x + 1, y + 1, boxWidth - 2, boxHeight - 2, tft->calculateColor(10, 10, 10));
    // painter->drawRect(x + 2, y + 2, boxWidth - 4, boxHeight - 4, tft->calculateColor(0, 0, 0));
    // painter->setPenColor(tft->calculateColor(10, 10, 10));
    // painter->drawLine(x + 1, y + 16, x + boxWidth - 2, y + 16);
    // painter->setTextSize(1);
    // painter->setTextColor(config->styleRedColor);
    // painter->drawText(name, x + 6, y + 5);
    // painter->setTextColor(currentColor);
    // if(isShowFull)
    // {
    //     for(int i = 0; i < text.size(); i++)
    //     {
    //         tft->drawText(text[i], x + 6, y + 21 + i * 12);
    //     }
    // }
    // else
    // {
    //     if(text.size() > 1)
    //     {
    //         tft->drawText(text[0].substring(0, text[0].length() - 3) + "...", x + 6, y + 21);
    //     }
    //     else
    //     {
    //         tft->drawText(text[0], x + 6, y + 21);
    //     }
        
    // }
}

void TableView::processSizeUpdate()
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

void TableView::update()
{
    Serial.println("TableView::update()");
    needUpdate = true;
    if (parent != nullptr)
    {
        parent->update();
    }
}

std::string TableView::getText()
{
    return text;
}

void TableView::setText(std::string _text)
{
    text = _text;
    processSizeUpdate();
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
