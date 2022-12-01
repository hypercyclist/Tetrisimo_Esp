#ifndef RESISTOR_H
#define RESISTOR_H

// This class describe physical resistor with his characteristics.
class Resistor
{
    private:
        int rating;
        int minADC;
        int maxADC;
    public:
        Resistor(int _rating, int _minADC, int _maxADC);
        ~Resistor();

        int getRating();
        void setRating(int _rating);

        void setADC(int _minADC, int _maxADC);
        
        int getMinADC();
        void setMinADC(int _minADC);
        
        int getMaxADC();
        void setMaxADC(int _maxADC);
};

#endif
