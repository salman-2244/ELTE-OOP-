#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include "Product.h"
#include "vehicle.h"

class Driver
{
    public:
        driver();
        Vehicle van;
        unsigned int distance(Vehicle &van,std::string &address);
        void doo();
        Product take();
        void deliver (Product &p);

};

#endif // DRIVER_H
