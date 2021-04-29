#include "Layout.h"
#include "Point.h"
#include "Size.h"

#include <SoftwareSerial.h>

Layout::Layout(std::shared_ptr<Widget> _parent)
    : 
    Widget(_parent),
    spacing(0),
    margin(5)
{
}

Layout::~Layout()
{
}



void Layout::render()
{
    for (int i = 0; i < childrens.size(); i++)
    {
        childrens[i]->draw();
    }
}

void Layout::addWidget(std::shared_ptr<Widget> _widget)
{
    childrens.push_back(_widget);
    countLayout();
    update();
}

// Notificate parent about changing size.
void Layout::countLayout()
{
}

void Layout::removeWidget(std::shared_ptr<Widget> _widget)
{
    int pos = Widget::indexOf(childrens, _widget);
    if (pos != -1) { return; }
    childrens[pos]->setParent(nullptr);
    childrens.erase( childrens.begin() + pos );
}



void Layout::focusNext()
{
}

void Layout::focusPrevious()
{
}



// void Layout::processChild(std::shared_ptr<Widget> _childWidget)
// {
//     addWidget(_childWidget);
// }
