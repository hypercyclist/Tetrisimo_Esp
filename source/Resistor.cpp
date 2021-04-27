#include "Resistor.h"

Resistor::Resistor(int _rating, int _minADC, int _maxADC) 
    : rating(_rating), minADC(_minADC), maxADC(_maxADC)
{
}

Resistor::~Resistor()
{
}

int Resistor::getRating()
{
    return rating;
}

void Resistor::setRating(int _rating)
{
    rating = _rating;
}

void Resistor::setADC(int _minADC, int _maxADC)
{
    minADC = _minADC;
    maxADC = _maxADC;
}

int Resistor::getMinADC()
{
    return minADC;
}

void Resistor::setMinADC(int _minADC)
{
    minADC = _minADC;
}

int Resistor::getMaxADC()
{
    return maxADC;
}

void Resistor::setMaxADC(int _maxADC)
{
    maxADC = _maxADC;
}