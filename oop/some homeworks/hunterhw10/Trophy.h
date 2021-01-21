#ifndef TROPHY_H_INCLUDED
#define TROPHY_H_INCLUDED

#include <iostream>


class Trophy
{
public:
    std::string getSpecies() const { return animal;}
protected:
        std::string animal;
        std::string place;
        std::string date;
        int weight;

};

class Lion : public Trophy{
public:
    Lion(std::string g) : gender(g) {};
    Lion(std::string animal_,std::string place_,std::string date_,int weight_,std::string gender_)
    {
        animal=animal_;place=place_;date=date_;weight=weight_;gender=gender_;
    };
private:
    std::string gender;
};

class Elephant : public Trophy{
public:
    Elephant(int trunk) : trunk_sz(trunk) {}
    Elephant(std::string animal_,std::string place_,std::string date_,int weight_,int trunk_sz_)
    {
        animal=animal_;place=place_;date=date_;weight=weight_;trunk_sz=trunk_sz_;
    };
private:
    int trunk_sz;
};

class Rhinoceros : public Trophy{
public:
    Rhinoceros(int w) : weighthorn(w) {}
    Rhinoceros(std::string animal_,std::string place_,std::string date_,int weight_,int weighthorn_)
    {
        animal=animal_;place=place_;date=date_;weight=weight_;weighthorn=weighthorn_;
    };
private:
    int weighthorn;
};




#endif // TROPHY_H_INCLUDED
