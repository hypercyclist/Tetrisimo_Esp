#ifndef BUTTON_H
#define BUTTON_H

class Point;

#include "Widget.h"

#include <memory>
#include <string>

// Class describe ingame widget button.
class Button : public Widget
{
    private:
        std::string text;
        int textSize;
    
    public:
        Button(std::string _text);
        ~Button();

        void render();
        void render(std::shared_ptr<Viewport> _viewport);
        void processSizeUpdate();
        
        std::string getText();
        void setText(std::string _text);
        int getTextSize();
        void setTextSize(int _textSize);
};

#endif
