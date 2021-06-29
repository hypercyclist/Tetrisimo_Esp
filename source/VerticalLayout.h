#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

class Widget;

#include "Layout.h"

#include <memory>
#include <vector>

// Class describe ingame widget vertical layout.
class VerticalLayout : public Layout
{
    public:
        VerticalLayout(std::shared_ptr<Widget> _parent = nullptr);
        ~VerticalLayout();

        //This function call execute fucntion of focused widget.
        void executeActiveWidget();
        void addWidget(std::shared_ptr<Widget> _widget);
        // If size of children widget changed, then we need to recount widgets
        // sizes, positions. Recount widgets position with function countLayout.
        void countLayout();

        void update();
        
        // Focus function focus first focusable widget in layout. focusNext and
        // focustPrevious fonctions move focus to other widgets.
        void focus();
        void unfocus();
        void focusNext();
        void focusPrevious();
};

#endif
