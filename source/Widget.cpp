#include "Widget.h"
#include "WidgetId.h"
#include "Painter.h"
#include "Point.h"
#include "Size.h"

#include <SoftwareSerial.h>

Widget::Widget(std::shared_ptr<Widget> _parent) 
    : 
    id( generateId() ),
    executeFunction(nullptr),
    parent(_parent),
    painter( Painter::getPainter() ),
    position( std::make_unique<Point>(0, 0) ), 
    size( std::make_unique<Size>(10, 10) ), 
    needUpdate(true),
    visible(true),
    focusability(false), 
    focused(false)
{
}

Widget::~Widget()
{
    WidgetId::removeId(id);
}



int Widget::getId()
{
    return id;
}

int Widget::generateId()
{
    return WidgetId::generateId();
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



int Widget::indexOf( std::vector< std::shared_ptr<Widget> >& _vector, 
    std::shared_ptr<Widget> _widget )
{
    int tempId = _widget->getId();
    for (int i = 0; i < _vector.size(); i++)
    {
        if (_vector[i]->getId() == tempId)
        {
            return i;
        }
    }
    return -1;
}

void Widget::removeChildren(std::shared_ptr<Widget> _children)
{
    int tempId = _children->getId();
    for (int i = 0; i < childrens.size(); i++)
    {
        if (childrens[i]->getId() == tempId)
        {
            childrens.erase( childrens.begin() + i );
        }
    }
}



Point Widget::getPosition()
{
    return *position;
}

void Widget::setPosition(Point _position)
{
    position = std::make_unique<Point>(_position);
    update();
}

int Widget::getX()
{
    return position->getX();
}

int Widget::getY()
{
    return position->getY();
}



Size Widget::getSize()
{
    return *size;
}

void Widget::setSize(Size _size)
{
    size = std::make_unique<Size>(_size);
    update();
}

int Widget::getWidth()
{
    return size->getWidth();
}

int Widget::getHeight()
{
    return size->getHeight();
}

void Widget::processSizeUpdate()
{
}



void Widget::draw()
{
    if (needUpdate)
    {
        render();
        updated();
    }
}

void Widget::render()
{
}

void Widget::update()
{
    needUpdate = true;
}

void Widget::updated()
{
    needUpdate = false;
}

bool Widget::isNeedUpdate()
{
    return needUpdate ? false : true;
}



void Widget::show()
{
    visible = true;
    update();
}

void Widget::hide()
{
    visible = false;
    update();
}

bool Widget::isVisible()
{
    return visible ? true : false;
}



void Widget::focus()
{
    focused = true;
    update();
}

void Widget::unfocus()
{
    focused = false;
    update();
}

bool Widget::isFocusable()
{
    return focusability ? true : false;
}

bool Widget::isFocused()
{
    return focused ? true : false;
}



// void Widget::processParent()
// {
//     if (parentWidget != nullptr)
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
