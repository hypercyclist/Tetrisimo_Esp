#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
class Point;
#include <string>
#include <memory>

class Button : public Widget
{
    private:
        std::string text;
        int textSize;
    public:
        Button(std::string _text);
        ~Button();
        void render();
        void processSizeUpdate();
        std::string getText();
        void setText(std::string _text);
        int getTextSize();
        void setTextSize(int _textSize);
};

#endif
