#include "vehicle.h"


void Vehicle::drive(int dist)
{
    startCar();
    tank.consumeFuel(dist*_consumption);
    stopCar();
}

void Vehicle::refuel()
{
    std::cout<<"Fuel is low refueling.. \n";
    unsigned int deficit = tank.getCapacity() - tank.getFuel();
    tank.addFuel(deficit);
}

bool Vehicle::CheckFuel(int distance) const
{
    unsigned int need = distance*_consumption;
    return need<=tank.getFuel();
}


void Vehicle::startCar()
{
    if(! (engine.isRunning()))
    {
        engine.start();
    }
}

void Vehicle::stopCar()
{
    if(engine.isRunning())
    {
        engine.stop();
    }

}
