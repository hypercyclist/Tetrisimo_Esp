#include "Layout.h"

#include "Point.h"
#include "Size.h"

#include "Log.h"

Layout::Layout(std::shared_ptr<Widget> _parent)
    : 
    Widget(),
    spacing(9),
    margin(5),
    adjusting(false)
{
}

Layout::~Layout()
{
}

void Layout::render()
{
    for (int i = 0; i < childrens.size(); i++)
    {
        childrens[i]->render();
    }
}

void Layout::addWidget(std::shared_ptr<Widget> _widget)
{
    childrens.push_back(_widget);
    _widget->setParent(shared_from_this());
    countLayout();
    // update();
}

std::shared_ptr<Widget> Layout::getWidget(int _index)
{
    return childrens[_index];
}

int Layout::getWidgetsCount()
{
    return childrens.size();
}

void Layout::removeWidget(std::shared_ptr<Widget> _widget)
{
    int pos = Widget::indexOf(childrens, _widget);
    if (pos != -1) { return; }
    childrens[pos]->setParent(nullptr);
    childrens.erase( childrens.begin() + pos );
}

void Layout::setAdjusting(bool _adjusting)
{
    adjusting = _adjusting;
}

bool Layout::isAdjusting()
{
    return adjusting;
}

// #include "Layout.h"
// #include "Widget.h"
// #include "Point.h"
// #include "Size.h"
// #include "Viewport.h"
//     offset(std::make_shared<Point>(0, 0))

void Layout::executeActiveWidget()
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

// Notificate parent about changing size.
void Layout::countLayout()
{
    // Инициировать перерасчет может каждый виджет, но начинать нужно от 
    // корневого виджета. Если есть родитель, то передать управление ему,
    // если нет, то начать расчет размера.
    if (parent) 
    { 
        parent->countLayout(); 
        return;
    }
    
    // Каждый виджет рекурсивно отвечает, сколько место ему нужно.
    Size widgetSize = processWidgetSize();

    // Расставляем виджеты на позиции.
    processWidgetPosition();
}

Size Layout::processWidgetSize() 
{
    // Если виджет в композиторе один, то просто возвращаем размер.
    if (childrens.size() == 0) return *size;

    // Иначе начинаем опрашивать дочерние виджеты и считать размер.
    int width = 0;
    int height = 0;

    // Если композитор вертикальный, то:
    // Ширина - самая большая ширина дочернего виджета.
    // Высота - сумма высот всех виджетов + отступы.
    if (layoutType == LayoutType::VERTICAL)
    {
        for (std::shared_ptr<Widget> widget : childrens) 
        {
            Size widgetSize = widget->processWidgetSize();
            width = widgetSize.getWidth() > width ? widgetSize.getWidth() : width;
            height += widgetSize.getHeight();
        }
        // Кол-во отступов горизонтальных = 2.
        // Кол-во отступов вертикальных = кол-во виджетов + 1.
        width += spacing * 2;
        height += spacing * (childrens.size() + 1);
    }
    // Если композитор горизонтальный, то:
    // Ширина - сумма широт всех виджетов + отступы.
    // Высота - самая большая высота дочернего виджета.
    else if (layoutType == LayoutType::HORIZONTAL)
    {
        for (std::shared_ptr<Widget> widget : childrens) 
        {
            Size widgetSize = widget->processWidgetSize();
            width += widgetSize.getWidth();
            height = widgetSize.getHeight() > height ? widgetSize.getHeight() : height;
        }
        // Кол-во отступов горизонтальных кол-во виджетов + 1.
        // Кол-во отступов вертикальных = 2.
        width += spacing * (childrens.size() + 1);
        height += spacing * 2;
    }
    size->setWidth(width);
    size->setHeight(height);

    return *size;
}

void Layout::processWidgetPosition()
{
    if (layoutType == LayoutType::VERTICAL)
    {
        int widgetWidth = position->getY();
        int widgetHeight = position->getX();
        for (std::shared_ptr<Widget> widget : childrens) 
        {
            int alignWidth = ( size->getWidth() - widget->getSize().getWidth() ) / 2;
            widget->setPosition(Point(widgetWidth + alignWidth, widgetHeight));
            widgetHeight += spacing;
            widgetHeight += widget->getHeight();
            widget->processWidgetPosition();
        }
    }
    else if (layoutType == LayoutType::HORIZONTAL)
    {
        int widgetWidth = position->getY();
        int widgetHeight = position->getX();
        for (std::shared_ptr<Widget> widget : childrens) 
        {
            widget->setPosition(Point(widgetWidth, widgetHeight));
            widgetWidth += spacing;
            widgetWidth += widget->getWidth();
            widget->processWidgetPosition();
        }
    }
}

LayoutType Layout::getLayoutType()
{
    return layoutType;
}

void Layout::setLayoutType(LayoutType _layoutType)
{
    layoutType = _layoutType;
}

// //notificate parent about changing size.
// void Layout::countLayout()
// {
//     // Log::println("Layout::countLayout()", "LOW");
//     int layoutWidth = size->getWidth();
//     int layoutHeight = size->getHeight();
//     int heightOfAllWidgets = 0;
//     int childrensCount = childrens.size();
//     if (adjusting)
//     {
//         // (Ширина экрана - Кол-во символов * Пикселей на букву) / 2
//         for (int i = 0; i < childrensCount; i++)
//         {
//             heightOfAllWidgets += childrens[i]->getSize().getHeight(); // + (margin * 2);
//         }
//         int freeSpace = heightOfAllWidgets < layoutHeight ? (layoutHeight - heightOfAllWidgets) / (childrensCount + 1) : 0;
//         int savedHeight = 0;

//         for(int i = 0; i < childrensCount; i++)
//         {
//             Size countedWidgetSize = childrens[i]->getSize();
//             int widgetX = ( layoutWidth - countedWidgetSize.getWidth() ) / 2;
//             int widgetY = savedHeight + freeSpace;
//             childrens[i]->setPosition( Point(widgetX - offset->getX(), widgetY - offset->getY()) );
//             savedHeight = widgetY + countedWidgetSize.getHeight();
//         }
//             //disable stretch
//             //use spacing and stretch
//     }
//     else
//     {
//         heightOfAllWidgets = spacing;
//         for (int i = 0; i < childrensCount; i++)
//         {
//             Size countedWidgetSize = childrens[i]->getSize();
//             // Log::println(countedWidgetSize.getWidth(), "LOW");
//             int widgetX = ( layoutWidth - countedWidgetSize.getWidth() ) / 2;
//             int widgetY = heightOfAllWidgets;
//             // Log::print("countLayout()", "LOW");
//             // Log::println(widgetX, "LOW");
//             childrens[i]->setPosition( Point(widgetX - offset->getX(), widgetY - offset->getY()) );
//             heightOfAllWidgets = widgetY + countedWidgetSize.getHeight() + spacing;
//         }
//     }
//     if (parent != nullptr) 
//     {
//         std::static_pointer_cast<Layout>(parent)->countLayout();
//     }
// }

void Layout::moveUp()
{
    focusPrevious();
}

void Layout::moveDown()
{
    focusNext();
}

void Layout::focus()
{
    Log::println("Layout::focus()", "LOW");
    for(int i = 0; i < childrens.size(); i++)
    {
        if ( childrens[i]->isFocusable() )
        {
            childrens[i]->focus();
            return;
        }
    }
}

void Layout::unfocus()
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

void Layout::focusNext()
{
    Log::println("Layout::focusNext()", "LOW");
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

void Layout::focusPrevious()
{
    Log::println("Layout::focusPrevious()", "LOW");
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

// // Y = focusedWidgetY + getHeight() + spacing - 160

// // Вниз и вверх смещает фокус виджетов и скролит экран.
// // Скролл вниз:
// // Если в пределах половины высоты экрана есть фокусируемый виджет, то:
// //     Если выбранный виджет влезает на текущем экране, то не скролить.
// //     Если выбранный виджет не влезает на текущем экране, то скролить, чтобы верх его был верхом     экрана.
// //     Если после виджета нет целого экрана, то выравнить скролл по дну сцены.
// // Если в пределах половины высоты экрана нет фокусируемого виджета, то скролить ниже на половину высоты экрана.
// //     Если при скроле достигли дна сцены, то выравнить скролл по дну сцены.

// //  Скролл вверх:
// // Если в пределах половины высоты экрана есть фокусируемый виджет, то:
// //     Если выбранный виджет влезает на текущем экране, то не скролить.
// //     Если выбранный виджет не влезает на текущем экране, то скролить, чтобы низ его был низом     экрана.
// //     Если после виджета нет целого экрана, то выравнить скролл по верху сцены.
// // Если в пределах половины высоты экрана нет фокусируемого виджета, то скролить выше на половину высоты экрана.
// //     Если при скроле достигли верха сцены, то выравнить скролл по верху сцены.
