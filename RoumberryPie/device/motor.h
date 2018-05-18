#ifndef MOTOR_H
#define MOTOR_H
#include "device.h"
/// The class Motor is_a Device.
class Motor: public Device
{
public:
    Motor(const std::string &id) : Device(id), speed_{0}{}
    virtual ~Motor(){setSpeed(0.0);}
    virtual void initialise() override; // C++11 override specifier
    virtual void reset() override;
    virtual void shutdown() override;
    void setSpeed(double speed);
    double getSpeed() const;

private:
    double speed_;
};
#endif // MOTOR_H
