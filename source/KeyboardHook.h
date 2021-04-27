#ifndef KEYBOARDHOOK
#define KEYBOARDHOOK

class PhysButton;
#include <vector>
#include <memory>

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

