#ifndef PALETTEVIEW_H
#define PALETTEVIEW_H

class Point;
class Color;

#include "Widget.h"

#include <memory>
#include <vector>

// Class describe ingame widget of palette view.
class PaletteView : public Widget
{
    public:
        PaletteView();
        ~PaletteView();

        void setParent(std::shared_ptr<Widget> _parent);

        void render();
        void processSizeUpdate();

        void update();

        void paintBlock(int _x, int _y, Color _color); // Need shared_ptr.
};

#endif
