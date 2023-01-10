#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include "Widget.h"
// #include "scene.h"
// #include "gridMenu.h"
// #include "lineEdit.h"
// #include "button.h"
// #include "keyboardButton.h"
// #include "mtft.h"
#include  <string>

class Button;
class GridLayout;

enum TextLayout
{
    ENGLISH_LOWER,
    ENGLISH_UPPER,
    NUMERIC_LOWER,
    NUMERIC_UPPER
};

class VirtualKeyboard : public Widget
{
    private:
        Widget* editableWidget;
        int editableWidgetLinesCount;
        std::vector<GridLayout*> layouts;
        GridLayout* currentLayout;
        std::vector<std::vector<std::vector<std::string>>> textLayouts;
        bool isLetterUpperCase;
        bool isNumsUpperCase;
        const int WIDTH_L = 36;
        const int WIDTH_M = 20;
        const int WIDTH_S = 12;
        void drawHeader();
        void drawKeyboard();
        void drawMenu();
        void setLayout(TextLayout);
        void setFunction(Button*);
    public:
        int editableWidgetOldX;
        int editableWidgetOldY;
        VirtualKeyboard();
        ~VirtualKeyboard();
        virtual void draw();
        void logic();
        void input(int);
        void setEditableWidget(Widget* _widget);
        void setForceUpdate();
};

#endif