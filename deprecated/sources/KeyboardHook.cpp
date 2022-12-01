#include "KeyboardHook.h"

#include "Keyboard.h"
#include "Log.h"
#include "PhysButton.h"


KeyboardHook::KeyboardHook(int _pinKeyboardADC)
    : pinKeyboardADC(_pinKeyboardADC)
{
}

KeyboardHook::~KeyboardHook()
{
}

void KeyboardHook::setPinKeyboardADC(int _pinKeyboardADC)
{
    pinKeyboardADC = _pinKeyboardADC;
}

int KeyboardHook::getPinKeyboardADC()
{
    return pinKeyboardADC;
}

void KeyboardHook::addButton(std::shared_ptr<PhysButton> _physButton)
{
    buttons.push_back(_physButton);
}

std::shared_ptr<PhysButton> KeyboardHook::getPressedButton()
{
    int inputADC = 5;//analogRead(pinKeyboardADC);
    // Log::println(inputADC, "LOW");
    for (int i = 0; i < buttons.size(); i++)
    {
        if ( buttons[i]->isPressed(inputADC) )
        {
            return buttons[i];
        }
    }
    return nullptr;
}
