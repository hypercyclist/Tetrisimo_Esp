#ifndef LAYOUT_H
#define LAYOUT_H

#include "Widget.h"

#include <memory>
#include <vector>

class Layout : public Widget
{
    protected:
        int spacing;
        int margin;
        bool adjusting;

    public:
        Layout(std::shared_ptr<Widget> _parent);
        ~Layout();
        void draw();
        virtual void render();
        void processChild(std::shared_ptr<Widget> _childWidget);
        virtual void addWidget(std::shared_ptr<Widget> _widget);
        virtual void removeWidget(std::shared_ptr<Widget> _widget);
        virtual void countLayout();
        
        virtual void focusNext();
        virtual void focusPrevious();
        void setAdjusting(bool _adjusting);
        bool isAdjusting();
};

#endif
