#ifndef POINT_H
#define POINT_H

class Point
{
    private:
        int x;
        int y;
    public:
        Point(int _x, int _y);
        ~Point();
        int getX();
        void setX(int _x);
        int getY();
        void setY(int _y);
};

#endif
