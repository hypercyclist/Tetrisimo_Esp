#ifndef SIZE_H
#define SIZE_H

// Default widget size structure.
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
