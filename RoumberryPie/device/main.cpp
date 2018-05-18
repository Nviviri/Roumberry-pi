#include <iostream>
#include <vector>
#include "device.h"
#include "motor.h"
#include "nulldevice.h"

using namespace std;

int main()
{
    Motor m1("motor1");
    Motor m2("motor2");
    Motor m3("motor3");
    NullDevice n1("null1");
    NullDevice n2("null2");
    NullDevice n3("null3");

    m1.setSpeed(10.0);
    m2.setSpeed(12.0);
    m3.setSpeed(18.0);

    cout << "speed" << m1.getSpeed() << endl;
    cout << "speed" << m2.getSpeed() << endl;
    cout << "speed" << m3.getSpeed() << endl;

    std::vector<Device*> v1{&m1,&m2,&n1,&n2,&n3};

    for(auto el: v1)
    {
        cout << el -> getID() << endl;
        el -> reset();
    }

    return 0;
}
