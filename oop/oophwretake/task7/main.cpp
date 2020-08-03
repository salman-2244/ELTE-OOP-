#include <iostream>
#include <iostream>
#include "library/maxsearch.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"


/**

urrent flower orders are stored in a textfile.
One order’s data may be found in multiple lines of the file.
One line consists of the customer’s ID, the name of the flower and how many the customer has ordered of that flower.
The file is ordered by customer ID.
Find a customer who has ordered at least three different kind of flowers.

*/
using namespace std;


struct Customer
{
    string id;
    string flower;
    int cntbought;
    friend istream& operator>>(istream &is, Customer &c)
    {
        is >> c.id >> c.flower >> c.cntbought;
    }
};

struct Output
{
    string id;
    string flowername;
    int cnt;
    Output() : id(""),cnt(0),flowername("") { }
    Output(string rhs_id,int rhs_d,string rhs_flower) : id(rhs_id),cnt(rhs_d),flowername(rhs_flower) { }
};


class distinctFlowers : public Summation<Customer, Output>
{
private:
    string _id;
public:
    distinctFlowers(const string &id) : _id(id){ }
protected:
    Output func(const Customer &p) const override { return Output(p.id,1,p.flower); }
    Output neutral() const override { return Output(); }
    Output add(const Output &a, const Output &b) const override { return Output(b.id,  a.cnt + b.cnt,b.flowername); }
    bool whileCond(const Customer &p) const override { return p.id == _id; }
    void first() override {}
};



class countEnum : public Enumerator<Output>
{
private:
    SeqInFileEnumerator<Customer>* _f;
    Output _freq;
    bool _end;
public:
    countEnum(const string &fname) { _f = new SeqInFileEnumerator<Customer>(fname); }
    ~countEnum() { delete _f; }
    void first() override { _f->first(); next(); }
    void next() override;
    Output current() const override { return _freq; }
    bool end() const override { return _end; }
};

void countEnum::next()
{
    if((_end = _f->end())) return;
    _freq.id = _f->current().id;
    distinctFlowers pr(_freq.id);
    pr.addEnumerator(_f);

    pr.run();
    _freq.cnt = pr.result().cnt;
}

class mySearch : public LinSearch<Output,false>
{
    bool cond(const Output& e) const override {return e.cnt >= 3;}
};


int main()
{
    try
    {
        mySearch pr;
        countEnum myenor("input.txt");
        pr.addEnumerator(&myenor);

        pr.run();
        if (pr.found())
            cout <<pr.elem().id << " is the most repeating.\n";
        else
            cout << "The file is empty!\n";
    }
    catch (SeqInFileEnumerator<Customer>::Exceptions exc)
    {
        cout << "File does not exist!\n";
        return 1;
    }
    return 0;
}
