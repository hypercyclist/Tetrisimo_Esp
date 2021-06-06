#include "VerticalLayout.h"
#include "Widget.h"
#include "Point.h"
#include "Size.h"

#include <SoftwareSerial.h>

VerticalLayout::VerticalLayout(std::shared_ptr<Widget> _parent)
    : 
    Layout(_parent)
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

void VerticalLayout::render()
{
    for (int i = 0; i < childrens.size(); i++)
    {
        childrens[i]->render();
    }
}

void VerticalLayout::addWidget(std::shared_ptr<Widget> _widget)
{
    childrens.push_back(_widget);
    _widget->setParent(shared_from_this());
    countLayout();
    update();
}

//notificate parent about changing size.
void VerticalLayout::countLayout()
{
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
            Serial.print("countLayout()");
            Serial.println(widgetX);
            childrens[i]->setPosition( Point(widgetX, widgetY) );
            heightOfAllWidgets = widgetY + countedWidgetSize.getHeight() + spacing;
        }
    }
}

void VerticalLayout::focus()
{
    for(int i = 0; i < childrens.size(); i++)
    {
        if ( childrens[i]->isFocusable() )
        {
            childrens[i]->focus();
            return;
        }
    }
}

void VerticalLayout::focusNext()
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
    update();
}

void VerticalLayout::focusPrevious()
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
    update();
}



// int cellHeight = childrensCount / ( widgetSize->getHeight() + (margin * 2) );
