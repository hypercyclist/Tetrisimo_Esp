#ifndef WIDGET_H
#define WIDGET_H

class Size;
class Point;
class Painter;
// #include "enable_shared_from_this.h"
#include <functional>
#include <memory>
#include <vector>

class Widget : public std::enable_shared_from_this<Widget> //Enable_shared_from_this<Widget>
{
    private:
        int id;
        int generateId();
    protected:
        std::shared_ptr<Widget> parentWidget;
        std::vector< std::shared_ptr<Widget> > childrens;
        std::unique_ptr<Point> widgetPosition;
        std::unique_ptr<Size> widgetSize;
        std::shared_ptr<Painter> painter;
        std::function<void()> executeFunction;
        bool widgetIsVisible;
        bool widgetCanBeFocused;
        bool widgetIsFocused;
        bool widgetIsNeedUpdate;
    public:
        Widget(std::shared_ptr<Widget> _parentWidget);
        ~Widget();
        void draw();
        void update();
        void updated();
        virtual void render();
        int getId();
        void execute();
        void setExecuteFunction(std::function<void()> _function);
        std::shared_ptr<Widget> getParent();
        void setParent(std::shared_ptr<Widget> _parentWidget);
        // virtual void processParent();
        // virtual void processChild(std::shared_ptr<Widget> _childWidget);
        // virtual void addChildren(std::shared_ptr<Widget> _children);
        virtual void removeChildren(std::shared_ptr<Widget> _children);
        Point getPosition();
        void setPosition(Point _widgetPosition);
        int getX();
        int getY();
        Size getSize();
        void setSize(Size _widgetSize);
        virtual void processSizeUpdate();
        int getWidth();
        int getHeight();
        void show();
        void hide();
        bool isVisible();
        bool isHidden();
        bool canBeFocused();
        void focus();
        void unfocus();
        bool isFocused();
        bool isUnfocused();
        bool isNeedUpdate();
        static int find(std::vector< std::shared_ptr<Widget> >& _vector, std::shared_ptr<Widget> _widget);
};

#endif