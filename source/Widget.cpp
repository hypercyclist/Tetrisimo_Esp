#include "Widget.h"
#include "WidgetId.h"
#include "Size.h"
#include "Point.h"
#include "Painter.h"
#include <SoftwareSerial.h>

Widget::Widget(std::shared_ptr<Widget> _parentWidget) 
    : parentWidget(_parentWidget),
    widgetPosition(std::make_unique<Point>(0, 0)), 
    widgetSize(std::make_unique<Size>(10, 10)), 
    painter(Painter::getPainter()),
    widgetIsVisible(true),
    widgetCanBeFocused(false), 
    widgetIsFocused(false),
    widgetIsNeedUpdate(true)
{
    id = generateId();
}

Widget::~Widget()
{
    WidgetId::removeId(id);
}

int Widget::generateId()
{
    id = WidgetId::generateId();
}

void Widget::draw()
{
    if(widgetIsNeedUpdate)
    {
        render();
        widgetIsNeedUpdate = false;
    }
}

void Widget::update()
{
    widgetIsNeedUpdate = true;
}

void Widget::updated()
{
    widgetIsNeedUpdate = false;
}

void Widget::render()
{
}

int Widget::getId()
{
    return id;
}

void Widget::execute()
{
    executeFunction();
}
void Widget::setExecuteFunction(std::function<void()> _function)
{
    executeFunction = _function;
}

std::shared_ptr<Widget> Widget::getParent()
{
    return parentWidget;
}

void Widget::setParent(std::shared_ptr<Widget> _parentWidget)
{
    parentWidget = _parentWidget;
    // processParent();
}

// void Widget::processParent()
// {
//     if(parentWidget != nullptr)
//     {
//         parentWidget->processChild( shared_from_this() );
//     }
// }

// void Widget::processChild(std::shared_ptr<Widget> _childWidget)
// {
// }

// void Widget::addChildren(std::shared_ptr<Widget> _children)
// {
//     childrens.push_back(_children);
// }

void Widget::removeChildren(std::shared_ptr<Widget> _children)
{
    int tempId = _children->getId();
    for(int i = 0; i < childrens.size(); i++)
    {
        if(childrens[i]->getId() == tempId)
        {
            childrens.erase( childrens.begin() + i );
        }
    }
}

Point Widget::getPosition()
{
    return *widgetPosition;
}

void Widget::setPosition(Point _widgetPosition)
{
    widgetPosition = std::make_unique<Point>(_widgetPosition);
}

int Widget::getX()
{
    return widgetPosition->getX();
}

int Widget::getY()
{
    return widgetPosition->getY();
}

Size Widget::getSize()
{
    return *widgetSize;
}

void Widget::setSize(Size _widgetSize)
{
    widgetSize = std::make_unique<Size>(_widgetSize);
}

void Widget::processSizeUpdate()
{
}

int Widget::getWidth()
{
    return widgetSize->getWidth();
}

int Widget::getHeight()
{
    return widgetSize->getHeight();
}

void Widget::show()
{
    widgetIsVisible = true;
}

void Widget::hide()
{
    widgetIsVisible = false;
}

bool Widget::isVisible()
{
    return widgetIsVisible ? true : false;
}

bool Widget::isHidden()
{
    return widgetIsVisible ? false : true;
}

bool Widget::canBeFocused()
{
    return widgetCanBeFocused ? true : false;
}

void Widget::focus()
{
    widgetIsFocused = true;
    update();
}

void Widget::unfocus()
{
    widgetIsFocused = false;
    update();
}

bool Widget::isFocused()
{
    return widgetIsFocused ? true : false;
}

bool Widget::isUnfocused()
{
    return widgetIsFocused ? false : true;
}

bool Widget::isNeedUpdate()
{
    return widgetIsNeedUpdate ? false : true;
}

int Widget::find(std::vector< std::shared_ptr<Widget> >& _vector, std::shared_ptr<Widget> _widget)
{
    int tempId = _widget->getId();
    for(int i = 0; i < _vector.size(); i++)
    {
        if(_vector[i]->getId() == tempId)
        {
            return i;
        }
    }
    return -1;
}
