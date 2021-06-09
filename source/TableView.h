#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "Widget.h"
class Point;

#include <string>
#include <vector>
#include <memory>

class TableView : public Widget
{
    private:
        std::string name;
        std::string textOriginal;
        std::vector<std::string> text;
        int WRAP_SIZE = 17;
        int textSize;
    
    public:
        TableView(std::string _text);
        TableView();
        ~TableView();

        void setParent(std::shared_ptr<Widget> _parent);

        void render();
        void processSizeUpdate();

        void update();
        
        void setName(std::string _name);
        std::string getName();
        void setText(std::string _text);
        std::string getText();
        int getTextSize();
        void setTextSize(int _textSize);
        int getLinesCount();
};

#endif
