#include <iostream>
#include <string>
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/summation.hpp"
#include "library/intervalenumerator.hpp"

using namespace std;

class IsPrime : LinSearch<int,true>
{
    bool cond(const int& e) const override
    {
        return e;
    }
};

class Assortment : public Summation<int, ostream>
{
public:
    Assortment(ostream* o) : Summation<int, ostream>::Summation(o) { }
protected:
    std::string func(const int& e) const override { return (to_string(e)+" "); }
    bool cond(const int& e) const {
    IsPrime pr;
    IntervalEnumerator myenor(2, e);
    pr.addEnumerator(&myenor);
    return pr.found();
    }

};

int main() ///ostream, vector
{
    Assortment pr(&cout);  // Assortment pr(&cout);
    SeqInFileEnumerator<int> myenor("input.txt");
    pr.addEnumerator(&myenor);

    pr.run();
    f.close();
    cout << endl;
    cout << endl;

    return 0;
}
