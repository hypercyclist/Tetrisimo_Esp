#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Widget.h"
#include <memory>

class Background : public Widget
{
    private:
    public:
        Background(std::shared_ptr<Widget> _parentWidget = nullptr);
        ~Background();
        void render();
        void drawNet();
        // virtual void logic();
        // virtual void input(int);
        // virtual void setForceUpdate();
};

#endif
