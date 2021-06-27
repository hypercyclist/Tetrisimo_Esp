#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// Color structure.
class Color
{
    private:
        int r;
        int g;
        int b;
        // Uint16_t colors need to native display painter library.
        uint16_t color16;
    public:
        Color(int _r, int _g, int _b);
        // Color(Color& _color); maybe need.
        ~Color();

        void update();

        uint16_t getUint16();
        uint16_t toUint16();
        
        void setColorRgb(int _r, int _g, int _b);

        int getR() const;
        void setR(int _r);

        int getG() const;
        void setG(int _g);

        int getB() const;
        void setB(int _b);
};

#endif
