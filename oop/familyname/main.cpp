#include <iostream>
#include "library/maxsearch.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"

using namespace std;

struct Person
{
    string name;
    string surname;
    friend istream& operator>>(istream &is, Person &p);
};

istream& operator>>(istream &is, Person &p)
{
    is >> p.name >> p.surname;
}

struct Output
{
    Output() {}
    Output(string rhs_name, int rhs_freq) : name(rhs_name), frequent(rhs_freq) { }
    string name;
    int frequent;

};

class CountNames : public Summation<Person, Output>
{
private:
    string _name;
public:
    CountNames(const string &name) : _name(name) {}
protected:
    Output func(const Person &p) const override { return Output(p.name, 1); }
    Output neutral() const override { return Output("", 0); }
    Output add(const Output &a, const Output &b) const override { return Output(a.name, a.frequent + b.frequent); }
    bool whileCond(const Person &p) const override { return p.name == _name; }
    void first() override {}
};

class FreqEnumerator : public Enumerator<Output>
{
private:
    SeqInFileEnumerator<Person>* _f;
    Output _freq;
    bool _end;
public:
    FreqEnumerator(const string &fname) { _f = new SeqInFileEnumerator<Person>(fname); }
    ~FreqEnumerator() { delete _f; }
    void first() override { _f->first(); next(); }
    void next() override;
    Output current() const override { return _freq; }
    bool end() const override { return _end; }
};

void FreqEnumerator::next()
{
    if((_end = _f->end())) return;
    _freq.name = _f->current().name;
    CountNames pr(_freq.name);
    pr.addEnumerator(_f);

    pr.run();
    _freq.frequent = pr.result().frequent;
}

class MostRepeating : public MaxSearch<Output,int>
{
protected:
    int func(const Output &e) const override { return e.frequent; }
};	



int main()
{
    try
    {
        MostRepeating pr;
        FreqEnumerator myenor("input.txt");
        pr.addEnumerator(&myenor);

        pr.run();
        if (pr.found())
            cout << pr.optElem().name << " is the most repeating.\n";
        else
            cout << "The file is empty!\n";
    }
    catch (SeqInFileEnumerator<Person>::Exceptions exc)
    {
        cout << "File does not exist!\n";
        return 1;
    }
    return 0;
}
