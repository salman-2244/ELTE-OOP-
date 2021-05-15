#ifndef FUELTANK_H_INCLUDED
#define FUELTANK_H_INCLUDED



class FuelTank
{
public:
    void addFuel(unsigned int amount) { fuel+= amount; }
    void consumeFuel(unsigned int amount) { fuel-= amount; }
    unsigned int getFuel() const { return fuel; }
    unsigned int getCapacity() const { return capacity; }
private:
    unsigned int fuel=25;
    unsigned int capacity=100;
};


#endif // FUELTANK_H_INCLUDED
