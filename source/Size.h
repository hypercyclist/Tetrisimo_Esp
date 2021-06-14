#ifndef SIZE_H
#define SIZE_H

class Size
{
    private:
        int width;
        int height;
    public:
        Size();
        Size(int, int);
        
        void setSize(int, int);

        void setWidth(int);
        int getWidth() const;

        void setHeight(int);
        int getHeight() const;

        // Size operator=(Size _size);
        bool operator==(const Size& foo);
        bool operator!=(const Size& foo);
};

#endif