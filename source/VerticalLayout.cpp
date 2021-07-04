#include "VerticalLayout.h"
#include "Widget.h"
#include "Point.h"
#include "Size.h"

#include <SoftwareSerial.h>

VerticalLayout::VerticalLayout(std::shared_ptr<Widget> _parent)
    : 
    Layout(_parent),
    screenRenderOffset(0)
{

}

VerticalLayout::~VerticalLayout()
{

}

void VerticalLayout::executeActiveWidget()
{
    int widgetIndex = -1;
    int childrensCount = childrens.size();
    for (int i = 0; i < childrensCount; i++) // Ищем виджет, который был в фокусе.
    {
        if ( childrens[i]->isFocused() )
        {
            widgetIndex = i;
            // Serial.println(i);
            break;
        }
    }
    if (widgetIndex == -1) // Если виджета в фокусе нет.
    {
        return;
    }
    else
    {
        childrens[widgetIndex]->execute();
    }
}

void VerticalLayout::addWidget(std::shared_ptr<Widget> _widget)
{
    childrens.push_back(_widget);
    _widget->setParent(shared_from_this());
    countLayout();
    // update();
}

//notificate parent about changing size.
void VerticalLayout::countLayout()
{
    Serial.println("VerticalLayout::countLayout()");
    int layoutWidth = size->getWidth();
    int layoutHeight = size->getHeight();
    int heightOfAllWidgets = 0;
    int childrensCount = childrens.size();
    if (adjusting)
    {
        // (Ширина экрана - Кол-во символов * Пикселей на букву) / 2
        for(int i = 0; i < childrensCount; i++)
        {
            heightOfAllWidgets += childrens[i]->getSize().getHeight(); // + (margin * 2);
        }
        int freeSpace = heightOfAllWidgets < layoutHeight ? (layoutHeight - heightOfAllWidgets) / (childrensCount + 1) : 0;
        int savedHeight = 0;

        for(int i = 0; i < childrensCount; i++)
        {
            Size countedWidgetSize = childrens[i]->getSize();
            int widgetX = ( layoutWidth - countedWidgetSize.getWidth() ) / 2;
            int widgetY = savedHeight + freeSpace;
            childrens[i]->setPosition( Point(widgetX, widgetY) );
            savedHeight = widgetY + countedWidgetSize.getHeight();
        }
            //disable stretch
            //use spacing and stretch
    }
    else
    {
        heightOfAllWidgets = spacing;
        for(int i = 0; i < childrensCount; i++)
        {
            Size countedWidgetSize = childrens[i]->getSize();
            // Serial.println(countedWidgetSize.getWidth());
            int widgetX = ( layoutWidth - countedWidgetSize.getWidth() ) / 2;
            int widgetY = heightOfAllWidgets;
            // Serial.print("countLayout()");
            Serial.println(widgetX);
            childrens[i]->setPosition( Point(widgetX, widgetY) );
            heightOfAllWidgets = widgetY + countedWidgetSize.getHeight() + spacing;
        }
    }
}

void VerticalLayout::update()
{
    Serial.println("VerticalLayout::update()");
    countLayout();
    needUpdate = true;
    if (parent != nullptr)
    {
        parent->update();
    }
}

void VerticalLayout::moveUp()
{
    focusPrevious();
}

void VerticalLayout::moveDown()
{
    for (int i = 0; i < childrens.size(); i++)
    {
        if (childrens[i].isFocusable() &&
            screenRenderOffset + (getHeight() / 2) > childrens[i].getY())
        {
            if ()
        }
        else
        {
            screenRenderOffset += getHeight() / 2; // Не забыть про то, что он может не влезть!
        }
        
    }
    focusNext();
}

void VerticalLayout::focus()
{
    Serial.println("VerticalLayout::focus()");
    for(int i = 0; i < childrens.size(); i++)
    {
        if ( childrens[i]->isFocusable() )
        {
            childrens[i]->focus();
            update();
            return;
        }
    }
}

void VerticalLayout::unfocus()
{
    Serial.println("unfocus");
    for (int i = 0; i < childrens.size(); i++) // Ищем виджет, который был в фокусе.
    {
        if ( childrens[i]->isFocused() )
        {
            childrens[i]->unfocus();
            Serial.println(i);
        }
    }
}

void VerticalLayout::focusNext()
{
    Serial.println("VerticalLayout::focusNext()");
    int widgetIndex = -1;
    int childrensCount = childrens.size();
    for (int i = 0; i < childrensCount; i++) // Ищем виджет, который был в фокусе.
    {
        if ( childrens[i]->isFocused() )
        {
            widgetIndex = i;
            // Serial.println(i);
            break;
        }
    }
    if (widgetIndex == -1) // Если виджета в фокусе нет.
    { 
        return;
    }
    if (widgetIndex + 1 != childrensCount) // Виджет не последний в группе.
    {
        for (int i = widgetIndex + 1; i < childrensCount; i++)
        {
            if ( childrens[i]->isFocusable() )
            {
                childrens[widgetIndex]->unfocus();
                childrens[i]->focus();
                return;
            }
        }
        for (int i = 0; i < widgetIndex; i++)
        {
            if ( childrens[i]->isFocusable() )
            {
                childrens[widgetIndex]->unfocus();
                childrens[i]->focus();
                return;
            }
        }
    }
    else // Виджет последний в группе. 
    {
        for (int i = 0; i < widgetIndex; i++)
        {
            if ( childrens[i]->isFocusable() )
            {
                childrens[widgetIndex]->unfocus();
                childrens[i]->focus();
                return;
            }
        }
    }
}

void VerticalLayout::focusPrevious()
{
    Serial.println("VerticalLayout::focusPrevious()");
    int widgetIndex = -1;
    int childrensCount = childrens.size();
    for (int i = 0; i < childrensCount; i++) // Ищем виджет, который был в фокусе.
    {
        if ( childrens[i]->isFocused() )
        {
            widgetIndex = i;
            // Serial.println(i);
            break;
        }
    }
    if (widgetIndex == -1) // Если виджета в фокусе нет.
    {
        return;
    }
    if (widgetIndex != 0) // Виджет не первый в группе.
    {
        for (int i = widgetIndex - 1; i >= 0; i--)
        {
            if ( childrens[i]->isFocusable() )
            {
                childrens[widgetIndex]->unfocus();
                childrens[i]->focus();
                return;
            }
        }
        for (int i = childrensCount - 1; i > widgetIndex; i--)
        {
            if ( childrens[i]->isFocusable() )
            {
                childrens[widgetIndex]->unfocus();
                childrens[i]->focus();
                return;
            }
        }
    }
    else // Виджет первый в группе. 
    {
        for (int i = childrensCount - 1; i > widgetIndex; i--)
        {
            if ( childrens[i]->isFocusable() )
            {
                childrens[widgetIndex]->unfocus();
                childrens[i]->focus();
                return;
            }
        }
    }
}

// Y = focusedWidgetY + getHeight() + spacing - 160

// Вниз и вверх смещает фокус виджетов и скролит экран.
// Скролл вниз:
// Если в пределах половины высоты экрана есть фокусируемый виджет, то:
//     Если выбранный виджет влезает на текущем экране, то не скролить.
//     Если выбранный виджет не влезает на текущем экране, то скролить, чтобы верх его был верхом     экрана.
//     Если после виджета нет целого экрана, то выравнить скролл по дну сцены.
// Если в пределах половины высоты экрана нет фокусируемого виджета, то скролить ниже на половину высоты экрана.
//     Если при скроле достигли дна сцены, то выравнить скролл по дну сцены.

//  Скролл вверх:
// Если в пределах половины высоты экрана есть фокусируемый виджет, то:
//     Если выбранный виджет влезает на текущем экране, то не скролить.
//     Если выбранный виджет не влезает на текущем экране, то скролить, чтобы низ его был низом     экрана.
//     Если после виджета нет целого экрана, то выравнить скролл по верху сцены.
// Если в пределах половины высоты экрана нет фокусируемого виджета, то скролить выше на половину высоты экрана.
//     Если при скроле достигли верха сцены, то выравнить скролл по верху сцены.
