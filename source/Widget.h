#ifndef WIDGET_H
#define WIDGET_H

class Painter;
class Point;
class Size;

#include <functional>
#include <memory>
#include <vector>

class Widget
{
    private:
        int id;
        int generateId();
    
    protected:
        std::function<void()> executeFunction;

        std::shared_ptr<Widget> parent;
        std::vector< std::shared_ptr<Widget> > childrens;
        std::shared_ptr<Painter> painter;
        
        std::unique_ptr<Point> position;
        std::unique_ptr<Size> size;
        bool needUpdate;
        bool visible;
        bool focusability;
        bool focused;
    
    public:
        Widget(std::shared_ptr<Widget> _parent);
        ~Widget();

        int getId();
        
        void execute();
        void setExecuteFunction(std::function<void()> _function);

        std::shared_ptr<Widget> getParent();
        void setParent(std::shared_ptr<Widget> _parent);

        static int indexOf( std::vector< std::shared_ptr<Widget> >& _vector, 
            std::shared_ptr<Widget> _widget);
        virtual void removeChildren(std::shared_ptr<Widget> _children);

        Point getPosition();
        void setPosition(Point _position);
        int getX();
        int getY();

        Size getSize();
        void setSize(Size _size);
        int getWidth();
        int getHeight();
        virtual void processSizeUpdate(); // check

        void draw();
        virtual void render();
        void update();
        void updated();
        bool isNeedUpdate();
        
        void show();
        void hide();
        bool isVisible();

        void focus();
        void unfocus();
        bool isFocusable();
        bool isFocused();
};

#endif

// : public std::enable_shared_from_this<Widget>
// virtual void processParent();
// virtual void processChild(std::shared_ptr<Widget> _childWidget);
// virtual void addChildren(std::shared_ptr<Widget> _children);
