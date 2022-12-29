#ifndef TEXTVIEW_H
#define TEXTVIEW_H

class Point;

#include "Widget.h"

#include <memory>
#include <string>
#include <vector>

// Class describe ingame widget table.
class TextView : public Widget
{
    private:
        std::string name;
        std::string textOriginal;
        std::vector<std::string> text;
        int wrapSize;
        int textSize;
    
    public:
        TextView(std::string _name, std::string _text);
        ~TextView();

        void setParent(std::shared_ptr<Widget> _parent);

        void render(std::shared_ptr<Viewport> _viewport);
        void processSizeUpdate();
        
        void setName(std::string _name);
        std::string getName();

        void setText(std::string _text);
        std::string getText();

        void setTextSize(int _textSize);
        int getTextSize();

        int getLinesCount();
};

#endif
