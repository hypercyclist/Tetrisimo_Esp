#ifndef CHECKBOX_H
#define CHECKBOX_H

class Point;

#include "Widget.h"

#include <memory>
#include <string>

// Class describe ingame widget checkbox.
class CheckBox : public Widget
{
    private:
        std::string text;
        int textSize;
        bool state;
    
    public:
        CheckBox(std::string _text, bool _state);
        CheckBox();
        ~CheckBox();

        void setParent(std::shared_ptr<Widget> _parent);

        void render();
        void processSizeUpdate();
        
        std::string getText();
        void setText(std::string _text);
        int getTextSize();
        void setTextSize(int _textSize);

        int getState();
        void setState(int _state);
};

#endif
