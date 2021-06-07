#include "Widget.h"
#include "WidgetId.h"
#include "Painter.h"
#include "Point.h"
#include "Size.h"

#include <SoftwareSerial.h>

Widget::Widget()
    : 
    id( generateId() ),
    executeFunction(nullptr),
    parent(nullptr),
    painter( Painter::getPainter() ),
    position( std::make_unique<Point>(1, 1) ), 
    size( std::make_unique<Size>(1, 1) ), 
    needUpdate(true),
    needCheck(true),
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
    return parent;
}

void Widget::setParent(std::shared_ptr<Widget> _parent)
{
    parent = _parent;
    update();
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
    update();
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
    for (int i = 0; i < childrens.size(); i++)
    {
        childrens[i]->render();
    }
}

void Widget::update()
{
    needUpdate = true;
    if (parent != nullptr)
    {
        parent->update();
    }
}

void Widget::updated()
{
    needUpdate = false;
}

bool Widget::isNeedUpdate()
{
    return needUpdate ? false : true;
}

void Widget::check()
{
    if (parent != nullptr)
    {
        parent->check();
    }
    needCheck = true;
}

void Widget::checked()
{
    needCheck = false;
}

bool Widget::isNeedCheck()
{
    return needCheck ? true : false;
}

void Widget::traverse()
{
    needCheck = false;
    for (int i = 0; i < childrens.size(); i++)
    {
        // childrens[i]->draw();
        if (childrens[i]->isNeedUpdate())
        {
            checked();
            updated();
            childrens[i]->render();
        }
        else if (childrens[i]->isNeedCheck())
        {
            checked();
            childrens[i]->check();
        }
    }
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
    render();
}

void Widget::unfocus()
{
    focused = false;
    render();
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
