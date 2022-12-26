#include "VerticalLayout.h"
#include "Widget.h"
#include "Point.h"
#include "Size.h"
#include "Viewport.h"

#include "Log.h"

VerticalLayout::VerticalLayout(std::shared_ptr<Widget> _parent)
    : 
    Layout(_parent),
    viewport(std::make_shared<Viewport>(Point(0, 0), Size(getWidth(), getHeight())))
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
            // Log::println(i, "LOW");
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

void VerticalLayout::render()
{
    for (int i = 0; i < childrens.size(); i++)
    {
        childrens[i]->render(viewport);
    }
}

//notificate parent about changing size.
void VerticalLayout::countLayout()
{
    Log::println("VerticalLayout::countLayout()", "LOW");
    int layoutWidth = size->getWidth();
    int layoutHeight = size->getHeight();
    int heightOfAllWidgets = 0;
    int childrensCount = childrens.size();
    if (adjusting)
    {
        // (Ширина экрана - Кол-во символов * Пикселей на букву) / 2
        for (int i = 0; i < childrensCount; i++)
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
        for (int i = 0; i < childrensCount; i++)
        {
            Size countedWidgetSize = childrens[i]->getSize();
            // Log::println(countedWidgetSize.getWidth(), "LOW");
            int widgetX = ( layoutWidth - countedWidgetSize.getWidth() ) / 2;
            int widgetY = heightOfAllWidgets;
            // Log::print("countLayout()", "LOW");
            // Log::println(widgetX, "LOW");
            childrens[i]->setPosition( Point(widgetX, widgetY) );
            heightOfAllWidgets = widgetY + countedWidgetSize.getHeight() + spacing;
        }
    }
}

void VerticalLayout::moveUp()
{
    focusPrevious();
}

void VerticalLayout::moveDown()
{
    int currentFocusedWidget = -1;
    int nextFocusableWidgetIndex = -1;
    for (int i = 0; i < childrens.size(); i++)
    {
        if (childrens[i]->isFocused())
        {
            currentFocusedWidget = i;
            break;
        }
    }
    if (currentFocusedWidget == -1)
    {
        return;
    }
    for (int i = currentFocusedWidget + 1; i < childrens.size(); i++)
    {
        if (childrens[i]->isFocusable())
        {
            nextFocusableWidgetIndex = i;
            break;
        }
    }
    if (currentFocusedWidget == -1)
    {
        return;
    }
    if (viewport->getPosition().getY() + getHeight() > childrens[nextFocusableWidgetIndex]->getY() + childrens[nextFocusableWidgetIndex]->getHeight())
    // if (viewport + (getHeight() / 2) > childrens[nextFocusableWidgetIndex].getY())
    {
        Log::println("Yes", "LOW");
        focusNext();
        // update();
    }
    else
    {
        Log::println("No", "LOW");
        viewport->setPosition( Point( viewport->getPosition().getX(), childrens[nextFocusableWidgetIndex]->getY() - spacing) );
        countLayout();
        focusNext();
    }
    // else
    // {
    //     viewport += getHeight() / 2; // Не забыть про то, что он может не влезть!
    // }
    // focusNext();
}

void VerticalLayout::focus()
{
    Log::println("VerticalLayout::focus()", "LOW");
    for(int i = 0; i < childrens.size(); i++)
    {
        if ( childrens[i]->isFocusable() )
        {
            childrens[i]->focus();
            return;
        }
    }
}

void VerticalLayout::unfocus()
{
    Log::println("unfocus", "LOW");
    for (int i = 0; i < childrens.size(); i++) // Ищем виджет, который был в фокусе.
    {
        if ( childrens[i]->isFocused() )
        {
            childrens[i]->unfocus();
            // Log::println(i, "LOW");
        }
    }
}

void VerticalLayout::focusNext()
{
    Log::println("VerticalLayout::focusNext()", "LOW");
    int widgetIndex = -1;
    int childrensCount = childrens.size();
    for (int i = 0; i < childrensCount; i++) // Ищем виджет, который был в фокусе.
    {
        if ( childrens[i]->isFocused() )
        {
            widgetIndex = i;
            // Log::println(i, "LOW");
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
    Log::println("VerticalLayout::focusPrevious()", "LOW");
    int widgetIndex = -1;
    int childrensCount = childrens.size();
    for (int i = 0; i < childrensCount; i++) // Ищем виджет, который был в фокусе.
    {
        if ( childrens[i]->isFocused() )
        {
            widgetIndex = i;
            // Log::println(i, "LOW");
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
