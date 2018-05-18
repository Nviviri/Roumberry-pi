#include "nulldevice.h"
#include <iostream>
using namespace std;

void NullDevice::initialise()
{
   cout << "null init" << endl;
}

void NullDevice::reset()
{
   cout << "null reset" << endl;
}

void NullDevice::shutdown()
{
   cout << "null shutdown" << endl;
}
