#ifndef TABLEVIEW_H
#define TABLEVIEW_H

class Point;

#include "Widget.h"

#include <memory>
#include <string>
#include <vector>

// Class describe ingame widget table.
class TableView : public Widget
{
    private:
        std::string name;
        std::vector<std::string> text;
        int wrapSize;
        int textSize;
    
    public:
        TableView(std::string _name);
        ~TableView();

        void setParent(std::shared_ptr<Widget> _parent);

        void render(std::shared_ptr<Viewport> _viewport);
        void processSizeUpdate();
        
        void setName(std::string _name);
        std::string getName();

        void addText(std::string _text);
        void removeText(int _index);
        std::string getText(int _index);

        void setTextSize(int _textSize);
        int getTextSize();

        int getLinesCount();
};

#endif
