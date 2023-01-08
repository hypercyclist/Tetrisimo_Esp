#include "Widget.h"

#include "Painter.h"
#include "Point.h"
#include "Size.h"
#include "WidgetId.h"

#include "Log.h"

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
    focused(false),
    maximized(true) { }

Widget::~Widget() { WidgetId::removeId(id); }

int Widget::getId() { return id; }

int Widget::generateId() { return WidgetId::generateId(); }

void Widget::execute() { executeFunction(); }
void Widget::setExecuteFunction(std::function<void()> _function) {
    executeFunction = _function;
}

std::shared_ptr<Widget> Widget::getParent() { return parent; }

void Widget::setParent(std::shared_ptr<Widget> _parent) { parent = _parent; }

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

Point Widget::getPosition() { return *position; }

void Widget::setPosition(Point _position) {
    position = std::make_unique<Point>(_position);
}

int Widget::getX() { return position->getX(); }

int Widget::getY() { return position->getY(); }

Size Widget::getSize() { return *size; }

void Widget::setSize(Size _size) { size = std::make_unique<Size>(_size); }

int Widget::getWidth() { return size->getWidth(); }

int Widget::getHeight() { return size->getHeight(); }

void Widget::processSizeUpdate() { }

void Widget::render()
{
    for (int i = 0; i < childrens.size(); i++)
    {
        childrens[i]->render();
    }
}

void Widget::show() { visible = true; }

void Widget::hide() { visible = false; }

bool Widget::isVisible() { return visible ? true : false; }

void Widget::focus() { focused = true; }

void Widget::unfocus() { focused = false; }

bool Widget::isFocusable() { return focusability ? true : false; }

bool Widget::isFocused() { return focused ? true : false; }

void Widget::maximize()
{
    maximized = true;
    processSizeUpdate();
}

void Widget::minimize()
{
    maximized = false;
    processSizeUpdate();
}

bool Widget::isMaximized() { return maximized; }
