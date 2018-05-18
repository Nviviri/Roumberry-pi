#include "motor.h"
#include <iostream>
using namespace std;

void Motor::initialise()
{
   speed_ = 0;
   cout << "motor init." << endl;
}

void Motor::reset()
{
   speed_ = 0;
   cout << "motor reset." << endl;
}

void Motor::shutdown()
{
   speed_ = 0;
   cout << "motor shutdown." << endl;
}
void Motor::setSpeed(double speed)
{
    speed_=speed;
}
double Motor::getSpeed() const
{
    return speed_;
}
