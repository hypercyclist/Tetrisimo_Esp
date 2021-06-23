#ifndef PORT_H
#define PORT_H

// Class for TCP port. Like a structure.
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
