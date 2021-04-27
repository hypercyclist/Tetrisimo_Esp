#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

class Widget;
#include "Layout.h"
#include <memory>
#include <vector>

class VerticalLayout : public Layout
{
    private:
    public:
        VerticalLayout(std::shared_ptr<Widget> _parentWidget = nullptr);
        ~VerticalLayout();
        void render();
        void addWidget(std::shared_ptr<Widget> _widget);
        void countLayout();
        void focusNext();
        void focusPrevious();
        void executeActiveWidget();
};

#endif