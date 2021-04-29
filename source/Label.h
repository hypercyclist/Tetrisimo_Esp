#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"
class Point;

#include <string>
#include <memory>

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
