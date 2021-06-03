#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Widget.h"

#include <memory>

class Background : public Widget
{
    private:
    public:
        Background();
        ~Background();

        void render();
        void drawNet();
};

#endif



// virtual void logic();
// virtual void input(int);
// virtual void setForceUpdate();
