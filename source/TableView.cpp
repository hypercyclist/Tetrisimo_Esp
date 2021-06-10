#include "TableView.h"
#include "Painter.h"
#include "Color.h"
#include "ResourceTheme.h"
#include "Point.h"
#include "Size.h"

TableView::TableView(std::string _name, std::string _text) 
    : 
    Widget(),
    name(_name),
    textOriginal(_text),
    textSize(1),
    WRAP_SIZE(17)
{
    focusability = true;
    int tempSizeCount = _text.length() / WRAP_SIZE;
    tempSizeCount = (float)tempSizeCount < (float)_text.length() / (float)WRAP_SIZE ? tempSizeCount + 1 : tempSizeCount;
    text.resize(tempSizeCount);
    for(int i = 0; i < text.size() - 1; i++)
    {
        text[i] = _text.substr(WRAP_SIZE * i, WRAP_SIZE * i + WRAP_SIZE);
    }
    text[text.size() - 1] = _text.substr(WRAP_SIZE * (text.size() - 1));
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

    int x = position->getX();
    int y = position->getY();
    int textPad = 4;
    int textHeight = 8;
    uint16_t focusColor = painter->getDrawColor().toUint16();
    uint16_t bacgroundColor = painter->getResourceTheme()->getBackgroundMenuColor().toUint16();

    painter->fillRect(x, y, getWidth(), getHeight(), bacgroundColor);
    painter->drawRect(x, y, getWidth(), getHeight(), Color(0, 0, 0).toUint16());
    painter->drawRect(x + 1, y + 1, getWidth() - 2, getHeight() - 2, Color(150, 150, 150).toUint16());
    painter->drawRect(x + 2, y + 2, getWidth() - 4, getHeight() - 4, Color(0, 0, 0).toUint16());
    painter->setDrawColor(Color(150, 150, 150));
    painter->drawLine(x + 1, y + textHeight + ( textPad * 2) + 1, x + getWidth() - 2, y + textHeight + ( textPad * 2) + 1);
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
    //         tft->drawText(text[0].substr(0, text[0].length() - 3) + "...", x + 6, y + 21);
    //     }
    //     else
    //     {
    //         tft->drawText(text[0], x + 6, y + 21);
    //     }
    // }
    painter->setDrawColor( painter->getResourceTheme()->getUnfocusColor() );
    painter->setTextSize(textSize);
    painter->drawText(textOriginal, *position);
}

void TableView::processSizeUpdate()
{
    int nextWidth;
    int nextHeight;
    if (parent != nullptr)
    {
        Size layoutSize = parent->getSize();
        nextWidth = layoutSize.getWidth() * 0.87f;
        int textPad = 4;
        int textHeight = 8;
        nextHeight = textHeight + ( textPad * 3) + 
            ( (textHeight + textPad) * getLinesCount() ); 
        update();
    }
    else
    {
        std::string russianCharacters = "абвгдеёжзиклмнопрстуфхцчшщъыьэюя";
        int realStringLength = 0;
        for (int i = 0; i < textOriginal.length(); )
        {
            realStringLength += 1;
            bool isRussianCharacter = false;
            for (int j = 0; j < russianCharacters.length(); j++)
            {
                if (textOriginal[i] == russianCharacters[j])
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

void TableView::setName(std::string _name)
{
    name = _name;
    processSizeUpdate();
}

std::string TableView::getName()
{
    return name;
}

void TableView::setText(std::string _text)
{
    textOriginal = _text;
    int tempSizeCount = _text.length() / WRAP_SIZE;
    tempSizeCount = (float)tempSizeCount < (float)_text.length() / (float)WRAP_SIZE ? tempSizeCount + 1 : tempSizeCount;
    tempSizeCount = tempSizeCount == 0 ? 1 : tempSizeCount;
    text.resize(tempSizeCount);
    for(int i = 0; i < text.size() - 1; i++)
    {
        text[i] = _text.substr(WRAP_SIZE * i, WRAP_SIZE * i + WRAP_SIZE);
    }
    text[text.size() - 1] = _text.substr(WRAP_SIZE * (text.size() - 1));
    processSizeUpdate();
}

std::string TableView::getText()
{
    return textOriginal;
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
    return text.size() > 0 ? text.size() : 1;
}
