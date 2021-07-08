#ifndef VIEWPORT_H
#define VIEWPORT_H

class Point;
class Size;

#include <memory>

// This class describe widget looking viewport.
class Viewport
{
    private:
        std::shared_ptr<Point> position;
        std::shared_ptr<Size> size;
    public:
        Viewport(Point _position, Size _size);
        ~Viewport();

        Point getPosition();
        void setPosition(Point _position);
        
        Size getSize();
        void setSize(Size _size);
};

#endif
