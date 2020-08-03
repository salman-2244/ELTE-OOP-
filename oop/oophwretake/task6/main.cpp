#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/maxsearch.hpp"

using namespace std;

bool isPrime(int n, int i = 2)
{
    // Base cases
    if (n <= 2)
        return (n == 2) ? true : false;
    if (n % i == 0)
        return false;
    if (i * i > n)
        return true;

    // Check for next divisor
    return isPrime(n, i + 1);
}


class Assortment : public Summation<int, ostream>
{
public:
    Assortment(ostream* o) : Summation<int, ostream>::Summation(o) { }
protected:
    std::string func(const int& e) const override { return (to_string(e)+" "); }
    bool cond(const int& e) const override { return e!=1 && isPrime(e); }

};


int main()
{
    Assortment pr(&cout);  // Assortment pr(&cout);
    SeqInFileEnumerator<int> myenor("input.txt");
    pr.addEnumerator(&myenor);

    pr.run();
    cout << endl;
    return 0;
}
