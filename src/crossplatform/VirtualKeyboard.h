#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include "Widget.h"
#include <string>
#include <memory>

class Button;
class Layout;

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
        std::shared_ptr<Widget> editableWidget;
        int editableWidgetLinesCount;
        std::vector<std::shared_ptr<Layout>> layouts;
        std::shared_ptr<Layout> currentLayout;
        std::vector<std::vector<std::vector<std::string>>> textLayouts;
        bool isLetterUpperCase;
        bool isNumsUpperCase;
        const int WIDTH_L = 36;
        const int WIDTH_M = 20;
        const int WIDTH_S = 12;
        // void drawHeader();
        // void drawKeyboard();
        // void drawMenu();
        // void setLayout(TextLayout);
        // void setFunction(Button*);
    public:
        int editableWidgetOldX;
        int editableWidgetOldY;
        VirtualKeyboard();
        ~VirtualKeyboard();
        void render();
        // void logic();
        // void input(int);
        // void setEditableWidget(std::shared_ptr<Widget> _widget);
        // void setForceUpdate();
};

#endif