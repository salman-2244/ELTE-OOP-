#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <iostream>
#include "fueltank.h"
#include "engine.h"
#include "Product.h"

enum Color{BLUE,YELLOW};

class Vehicle
{
    public:
        Vehicle(): _consumption(4),Capacity(5) {};
        FuelTank tank;
        Engine engine;
        std::vector<Product> cargo;
        int Capacity;
        bool CheckFuel(int distance) const;
        void refuel();
        void drive(int dist);
        void startCar();
        void stopCar();
        Color color;

    private:
        unsigned int _consumption;
};

#endif // VEHICLE_H
