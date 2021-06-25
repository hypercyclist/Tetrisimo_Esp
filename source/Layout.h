#ifndef LAYOUT_H
#define LAYOUT_H

#include "Widget.h"

#include <memory>
#include <vector>

// Class describe ingame widget layout. This is the base class for layouts.
class Layout : public Widget
{
    protected:
        int spacing;
        int margin;
        // If adjusting is true, then children widgets fill whole height,
        // else widgets take their height + spacings, align to top.
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
