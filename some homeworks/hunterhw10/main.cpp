#include <iostream>
#include "hunter.h"
#include "Trophy.h"
using namespace std;

int countOfLions(vector <Trophy> &trophies);

int main()
{
    Hunter Person("Jack",32);
    Lion first("lion","forest","2007.08.18",54,"male");
    Elephant second("elephant","forest","2014.06.20",108,27);
    Lion third("lion","forest","2009.04.12",38,"female");
    Person.trophies = {first,second,third};

    int lions=countOfLions(Person.trophies);


    cout<<"Count of lions that hunter killed " << lions <<endl;

    return 0;
}

int countOfLions(vector <Trophy> &trophies)
{
    int c_lions=0;
    for(int i=0;i<trophies.size();i++)
    {
        if(trophies[i].getSpecies() == "lion")
        {
            ++c_lions;
        }
    }
    return c_lions;
}

