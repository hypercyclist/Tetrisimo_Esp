#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Widget.h"

class Background : public Widget
{
    public:
        Background();
        ~Background();
        void render();
        void drawNet();
};

#endif
