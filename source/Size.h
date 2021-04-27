#ifndef SIZE_H
#define SIZE_H

class Size
{
    private:
        int width;
        int height;
    public:
        // Size();
        Size(int, int);
        // Size operator=(Size _size);
        
        void setSize(int, int);

        void setWidth(int);
        int getWidth();

        void setHeight(int);
        int getHeight();
};

#endif