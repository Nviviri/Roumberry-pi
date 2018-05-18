#ifndef NULLDEVICE_H
#define NULLDEVICE_H
#include "device.h"
#include <iostream>
using namespace std;

class NullDevice: public Device
{
public:
    NullDevice(const std::string &id): Device(id){}
    virtual ~NullDevice(){cout<<"null device destructor"<<endl;}
    virtual void initialise() override; // C++11 override specifier
    virtual void reset() override;
    virtual void shutdown() override;

};
#endif // NULLDEVICE_H
