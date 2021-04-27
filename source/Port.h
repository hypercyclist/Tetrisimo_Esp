#ifndef PORT_H
#define PORT_H

class Port
{
    private:
        int portAddress;
    public:
        Port(int _portAddress);
        ~Port();
        int getPortAddress();
        void setPortAddress(int _portAddress);
};

#endif