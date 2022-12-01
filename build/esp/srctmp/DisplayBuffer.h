#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#include <map>

class DisplayBuffer
{
    private:
        int bufferSize;
        char* buffer;

        char getLowerBits(char* _byte);
        char getUpperBits(char* _byte);
        void setLowerBits(char* _byte, char* _colorCode);
        void setUpperBits(char* _byte, char* _colorCode);
        void printBits(char& _byte);

    public:
        static const char colorCodes[16];
        static std::map<uint16_t, char> bindedCodes;
        static std::map<char, uint16_t> bindedColors;

        DisplayBuffer(int _bufferSize);
        // DisplayBuffer(const DisplayBuffer &_buffer);
        ~DisplayBuffer();

        void clearBuffer();
        static void bindColor(uint16_t _color, char _colorCode);
        void setColor(int _index, uint16_t _color);
        uint16_t getColor(int _index);
        void test(uint16_t _color);
};

#endif //DISPLAYBUFFER_H