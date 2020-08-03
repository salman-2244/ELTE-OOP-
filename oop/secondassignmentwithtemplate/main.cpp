#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/counting.hpp"
#include "library/maxsearch.hpp"

using namespace std;


struct Fish
{
    string name;
    int sz;
    friend istream &operator>>(istream &is,Fish &f) { is>>f.name>>f.sz; return is; }
};

class FishCount : public Counting<Fish> { };

struct Contest
{
    string name;
    string championship;
    bool noFish;
    friend istream &operator>>(istream &is,Contest &c)
    {
        string line;
        getline(is,line,'\n');
        stringstream ss(line);
        ss >> c.name >> c.championship;
        FishCount pr;
        pr


        return is;
    }

};


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
