#ifndef WIDGET_H
#define WIDGET_H

class Painter;
class Point;
class Size;
class Viewport;

#include <functional>
#include <memory>
#include <vector>

class Widget : public std::enable_shared_from_this<Widget>
{
    private:
        // Created widget get unique ID. Now this function is not used, but work.
        int id;
        int generateId();
    
    protected:
        // If widget focusability is true, after pressing button OK, widget
        // exec attached function.
        std::function<void()> executeFunction;
        // All widgets integrated in layouts, other widgets have parent widget.
        // Widget without parent will not be updated in a case of it was changed.
        // Some widget have childrens, example is layouts. Render function checking
        // necessaty of update childrens of widgets, than render it.
        std::shared_ptr<Widget> parent;
        std::vector< std::shared_ptr<Widget> > childrens;
        // Painter object draw widget graphics. Painter draw on selected display.
        std::shared_ptr<Painter> painter;
        // Layouts automaticaly control position and size of widget. If widget
        // haven't parent, then we need take care about his position, size and updates.
        std::unique_ptr<Point> position;
        std::unique_ptr<Size> size;
        // Flags of widgets that can answer to parent of this widget on questions,
        // is this child or child of this child need to be updated? is widget
        // visible or have focusability, is it focused or not.
        bool needUpdate;
        bool needCheck;
        bool visible;
        bool focusability;
        bool focused;
        bool maximized;
    
    public:
        Widget();
        ~Widget();
        int getId();
        void execute();
        // Setting function to execute over lambda.
        void setExecuteFunction(std::function<void()> _function);
        std::shared_ptr<Widget> getParent();
        virtual void setParent(std::shared_ptr<Widget> _parent);
        // Searching widget by pointer in widgets array.
        static int indexOf( std::vector< std::shared_ptr<Widget> >& _vector, 
            std::shared_ptr<Widget> _widget);
        virtual void removeChildren(std::shared_ptr<Widget> _children);
        Point getPosition();
        void setPosition(Point _position);
        // If we just need get int of position or size we can do it without 
        // intermediate Point or Size value.
        int getX();
        int getY();
        Size getSize();
        void setSize(Size _size);
        int getWidth();
        int getHeight();
        // If we change widget text or icon it also need to update his size.
        // Updating size things described in this function. Layouts take care
        // about positions.
        virtual void processSizeUpdate();
        // Maybe there are no place for draw function. Now we use travers and 
        // render functions. As run platform limited in memory and clock speed
        // we haven't time for update full scene as on powerfull PC.
        // Render function really redraw widget. Travers function check is this
        // widget really need to be updated and don't render it if possible.
        void draw(); // deprecated
        virtual void render();
        virtual void render(std::shared_ptr<Viewport> _viewport);
        // If function update executed it set request flag to update whole branch
        // of widgets. Using updateOne function ensure engine that we don't need
        // to update branch, only one widget, because size of widget not changed,
        // so it can be redrawed over old widget render. This technology saves a
        // lot of processor time and our eyes don't see redrawing on the display.
        // Also display don't have double buffering. Understand situation.
        virtual void update();
        void updateOne();
        // Updated function set flag that mean we not need update widget.
        void updated();
        bool isNeedUpdate();
        // Check function use to route our engine on widgets branch to widget
        // that only need redraw, without update whole widget branch.
        virtual void check();
        void checked();
        bool isNeedCheck();
        // Travers function navigate engine further on branch line.
        void traverse();
        // Functions show or hide widget on display.
        void show();
        void hide();
        bool isVisible();
        // When we go up and down in the menu we must focus next widget and unfocus
        // current. Also we must check is this widget focusable or not. For example
        // Button is focusable, lable not.
        virtual void focus();
        void unfocus();
        bool isFocusable();
        bool isFocused();
        // Pursuing compactness we can minimize our widget or maximize vice versa.
        void maximize();
        void minimize();
        bool isMaximized();
};

#endif
