#ifndef LINEEDIT_H
#define LINEEDIT_H

class Point;

#include "Widget.h"

#include <memory>
#include <string>
#include <vector>

// Class describe ingame widget editing line.
class LineEdit : public Widget
{
    private:
        std::string name;
        std::string textOriginal;
        std::vector<std::string> text;
        int wrapSize;
        int textSize;
    
    public:
        LineEdit(std::string _name, std::string _text);
        ~LineEdit();

        void setParent(std::shared_ptr<Widget> _parent);

        void render();
        void processSizeUpdate();

        void update();
        
        void setName(std::string _name);
        std::string getName();

        void setText(std::string _text);
        std::string getText();

        void setTextSize(int _textSize);
        int getTextSize();

        int getLinesCount();
};

#endif
