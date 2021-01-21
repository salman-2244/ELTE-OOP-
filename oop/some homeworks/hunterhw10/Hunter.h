#ifndef HUNTER_H_INCLUDED
#define HUNTER_H_INCLUDED

#include <iostream>
#include <vector>
#include "Trophy.h"
class Hunter
{
    public:
        Hunter(){};
        Hunter(std::string name_, int age_): name(name_),age(age_) { } ;
        std::vector<Trophy> trophies;
    private:
        std::string name;
        int age;
};



#endif // HUNTER_H_INCLUDED
