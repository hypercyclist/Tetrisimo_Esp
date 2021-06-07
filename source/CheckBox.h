#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Widget.h"
class Point;

#include <string>
#include <memory>

class CheckBox : public Widget
{
    private:
        std::string text;
        int textSize;
    
    public:
        CheckBox(std::string _text);
        CheckBox();
        ~CheckBox();

        void setParent(std::shared_ptr<Widget> _parent);

        void render();
        void processSizeUpdate();

        void update();
        
        std::string getText();
        void setText(std::string _text);
        int getTextSize();
        void setTextSize(int _textSize);
};

#endif
