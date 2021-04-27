#include "KeyboardHook.h"
#include "PhysButton.h"
#include <wiring_private.h>

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
    int inputADC = analogRead(pinKeyboardADC);
    // Serial.println(inputADC);
    for (int i = 0; i < buttons.size(); i++)
    {
        if ( buttons[i]->isPressed(inputADC) )
        {
            return buttons[i];
        }
    }
    return nullptr;
}


// #include <Резюме.h>

// // Комментарий.
// /*Гений - это не человек
// - это крокодил гена в тапках*/

// int main()
// {
//     std::cout << "Текст для вывода" << std::endl; 
//     return приглашение на работу;
// }