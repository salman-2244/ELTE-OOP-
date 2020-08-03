#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"



using namespace std;

/**
A motorbike service has registered the repairs of the different motorcycles in a sequential input file.
One line of the file contains the customer’s name, the type of the motorbike, and the repairs: name-price pairs.
The file is ordered by customer names. You can assume that the file’s structure is correct.
One sample line of the file:
Customer1 YamahaAxis50 oilchange 20 motorblock 100 cablesealing 10.
How many customers have at least two motorbikes that had a service more expensive than 95 euros?

*/

struct Repair
{
    string name;
    int cost;
    friend istream& operator>>(istream &is, Repair &r)
    {
        is>>r.name >> r.cost;
        return is;
    }

};

struct Result
{
    int co;
    string bike;
    Result() : co(0),bike("") {}
    Result(string b,int cost) : co(cost), bike(b) {}
};

class sumAll : public Summation<Repair,Result>
{
    Result func(const Repair& e) const override {return Result(e.name,e.cost);}
    Result neutral() const override {return Result();}
    Result add(const Result& a, const Result& b) const override { return Result(b.bike,a.co + b.co); }
};

class myCount : public Summation<Output,int>
{
    int func(const Result& e) const override {return e.co>95 ? 1 : 0;}
    int neutral() const override {return 0;}
    int add( const int& a, const int& b) const override { return a+b; }
};

struct Output
{
    string customer;
    string motorbike;
    int totalcost;
    int highcostcounter;
    friend istream& operator>>(istream &is, Output &o)
    {
        string line;
        getline (is,line,'\n');
        stringstream ss(line);
        ss>>o.customer>>o.totalcost;
        StringStreamEnumerator<Repair> ssenor(ss);
        sumAll pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        o.totalcost = pr.result().co;
        StringStreamEnumerator<Repair> ssenor2(ss);
        myCount pr2;
        pr2.addEnumerator(&ssenor);
        pr2.run();
        o.highcostcounter = pr2.result();


        return is;
    }
};



int main()
{
/*
    try
    {

    }
    catch (SeqInFileEnumerator<Output>::Exceptions err)
    {
        cerr<<"File not found!\n";
        return 1;
    }
*/
    return 0;
}
