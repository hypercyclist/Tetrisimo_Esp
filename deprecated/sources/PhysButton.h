#ifndef PHYSBUTTON_H
#define PHYSBUTTON_H

class Resistor;

#include <memory>

// This class describe physical button with his characteristics.
class PhysButton
{
    private:
        std::unique_ptr<Resistor> resistor;
    public:
        PhysButton(Resistor _resistor);
        PhysButton(PhysButton& _fromPhysButton);
        ~PhysButton();
        bool isPressed(int _inputADC);
        Resistor getResistor();
        void setResistor(Resistor _resistor);
};

#endif
