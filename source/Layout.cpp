#include "Layout.h"

#include "Point.h"
#include "Size.h"

#include "DefineLog.h"

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

// void Layout::draw()
// {
//     for (int i = 0; i < childrens.size(); i++)
//     {
//         childrens[i]->draw();
//     }
// }

void Layout::render()
{
    // countLayout();
    for (int i = 0; i < childrens.size(); i++)
    {
        childrens[i]->render();
    }
}

void Layout::addWidget(std::shared_ptr<Widget> _widget)
{
    childrens.push_back(_widget);
    countLayout();
    update();
}

std::shared_ptr<Widget> Layout::getWidget(int _index)
{
    return childrens[_index];
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

void Layout::setAdjusting(bool _adjusting)
{
    adjusting = _adjusting;
}

bool Layout::isAdjusting()
{
    return adjusting;
}
