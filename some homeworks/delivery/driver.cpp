#include "driver.h"

void Driver::doo()
{
    std::cout<< "Driving .. \n";
    int c=0;
    while(c<van.Capacity)
    {
        van.cargo.push_back(take());
        c++;
    }
    for(p:van.cargo)
    {
        deliver(p);
    }

}
Product Driver::take()
{
    std::cout<<"Product is taken \n";
    Product p("Budapest");
    return p;
}


unsigned int Driver::distance(Vehicle &van,std::string &address)
{
    return 8;
}

void Driver::deliver (Product &p)
{
    std::cout<< "Product is delivered. " << p.address << "\n";
    unsigned int dist=distance(van,p.address);
    if (!van.CheckFuel(dist))
    {
        van.refuel();
    }
    van.drive(dist);
    van.cargo.pop_back();
}
