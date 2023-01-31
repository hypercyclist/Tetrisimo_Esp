#include "Widget.h"

#include "Layout.h"
#include "Painter.h"
#include "Point.h"
#include "Size.h"
#include "WidgetId.h"

#include "Log.h"
#include <iostream>

Widget::Widget()
    : 
    id( generateId() ),
    executeFunction(nullptr),
    parent(nullptr),
    layout(nullptr),
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

std::shared_ptr<Layout> Widget::getLayout()
{
    if (layout) return layout;
    else 
    {
        layout = std::make_shared<Layout>( shared_from_this() );
        return layout;
    }
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

// Notificate parent about changing size.
void Widget::countLayout()
{
    // Инициировать перерасчет может каждый виджет, но начинать нужно от 
    // корневого виджета. Если есть родитель, то передать управление ему,
    // если нет, то начать расчет размера.
    if (parent) 
    { 
        parent->countLayout();
        return;
    }
    // Log::print("root starts processWidgetSize ", "LOW");
    // std::cout << typeid(this).name() << std::endl;
    // std::cout << this << std::endl;
    // Каждый виджет рекурсивно отвечает, сколько место ему нужно.
    Size widgetSize = processWidgetSize();

    // Расставляем виджеты на позиции.
    processWidgetPosition();
}

Size Widget::processWidgetSize() 
{
    // Если виджет в композиторе один, то просто возвращаем размер.
    if (getLayout()->getWidgetsCount() == 0) return *size;
    Log::println("Size Widget::processWidgetSize() ", "LOW");

    Size childrensSize = getLayout()->processWidgetSize();
    if(parent) {
        size = std::make_unique<Size>(childrensSize);
    } else {
        Log::println("Size: " + std::to_string(size->getWidth()) + " " + std::to_string(size->getHeight()), "LOW");
    }
    getLayout()->setSize(*size);

    return *size;
}

void Widget::processWidgetPosition()
{
    getLayout()->setPosition(*position);
    getLayout()->processWidgetPosition();
}

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
    countLayout();
}

void Widget::minimize()
{
    maximized = false;
    countLayout();
}

bool Widget::isMaximized() { return maximized; }
