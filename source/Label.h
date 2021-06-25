#ifndef LABEL_H
#define LABEL_H

class Point;

#include "Widget.h"

#include <memory>
#include <string>

// Class describe ingame widget label.
class Label : public Widget
{
    private:
        std::string text;
        int textSize;
        bool underlined;
    
    public:
        Label(std::string _text);
        ~Label();

        void render();
        void processSizeUpdate();
        
        std::string getText();
        void setText(std::string _text);
        int getTextSize();
        void setTextSize(int _textSize);
        
        bool isUnderlined();
        void setUnderline(bool _underline);
};

#endif
