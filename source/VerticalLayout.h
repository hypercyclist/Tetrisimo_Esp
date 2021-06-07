#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include "Layout.h"
class Widget;

#include <memory>
#include <vector>

class VerticalLayout : public Layout
{
    private:
    public:
        VerticalLayout(std::shared_ptr<Widget> _parent = nullptr);
        ~VerticalLayout();

        void executeActiveWidget();
        // void render();
        void addWidget(std::shared_ptr<Widget> _widget);
        void countLayout();

        void update();
        
        void focus();
        void focusNext();
        void focusPrevious();
};

#endif