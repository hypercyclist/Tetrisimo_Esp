#ifndef KEYBOARDHOOK
#define KEYBOARDHOOK

class PhysButton;

#include <memory>
#include <vector>

// This class help to determine which physical button was pressed. Firstly
// we add all buttons, that it must controll, then check is buttons pressed.
class KeyboardHook
{
    private:
        int pinKeyboardADC;
        std::vector< std::shared_ptr<PhysButton> > buttons;
    public:
        KeyboardHook(int _pinKeyboardADC);
        ~KeyboardHook();
        void setPinKeyboardADC(int _pinKeyboardADC);
        int getPinKeyboardADC();
        void addButton(std::shared_ptr<PhysButton> _physButton);
        std::shared_ptr<PhysButton> getPressedButton();
};

#endif
