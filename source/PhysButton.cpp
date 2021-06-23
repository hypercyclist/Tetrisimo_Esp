#include "PhysButton.h"

#include "Resistor.h"

PhysButton::PhysButton(Resistor _resistor)
    : resistor( std::make_unique<Resistor>(_resistor) )
{
    
}

PhysButton::PhysButton(PhysButton& _fromPhysButton)
{
    resistor = std::make_unique<Resistor>( _fromPhysButton.getResistor() );
}

PhysButton::~PhysButton()
{
    
}

bool PhysButton::isPressed(int _inputADC)
{
    if( resistor->getMinADC() < _inputADC && _inputADC < resistor->getMaxADC() )
    {
        return true;
    }
    return false;
}

Resistor PhysButton::getResistor()
{
    return *resistor;
}

void PhysButton::setResistor(Resistor _resistor)
{
    resistor = std::make_unique<Resistor>(_resistor);
}
