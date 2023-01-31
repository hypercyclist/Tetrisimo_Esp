#ifndef LAYOUT_H
#define LAYOUT_H

#include "Widget.h"

#include <memory>
#include <vector>

// Class describe ingame widget layout.
class Layout : public Widget
{
    protected:
        int margin;
        int spacing;
        // If adjusting is true, then children widgets fill whole height,
        // else widgets take their height + spacings, align to top.
        bool adjusting;
        LayoutType layoutType;

    public:
        Layout(std::shared_ptr<Widget> _parent = nullptr);
        ~Layout();
        LayoutType getLayoutType();
        void setLayoutType(LayoutType _layoutType);
        virtual void render();
        void processChild(std::shared_ptr<Widget> _childWidget);
        virtual void addWidget(std::shared_ptr<Widget> _widget);
        std::shared_ptr<Widget> getWidget(int _index);
        int getWidgetsCount();
        virtual void removeWidget(std::shared_ptr<Widget> _widget);
        virtual Size processWidgetSize();
        void processWidgetPosition();
        //This function call execute fucntion of focused widget.
        void executeActiveWidget();
        void moveUp();
        void moveDown();
        // Focus function focus first focusable widget in layout. focusNext and
        // focustPrevious fonctions move focus to other widgets.
        virtual void focusNext();
        virtual void focusPrevious();
        void focus();
        void unfocus();
        void setAdjusting(bool _adjusting);
        bool isAdjusting();
};

#endif

// class Size;
// class Viewport;

//     private: 
//         std::shared_ptr<Point> offset;
// };
