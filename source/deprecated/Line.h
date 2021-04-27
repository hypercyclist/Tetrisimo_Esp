#ifndef LINE_H
#define LINE_H

#include "Widget.h"
class Point;
#include <memory>

class Line : public Widget
{
    private:
        std::shared_ptr<Point> pointA;
        std::shared_ptr<Point> pointB;
        int lineWidth;
        int lineThickness;
    public:
        Line();
        ~Line();
        void render();
        int getWidth();
        void setWidth(int _lineWidth);
        int getLineThickness();
        void setLineThickness(int _lineWidth);
};

#endif
