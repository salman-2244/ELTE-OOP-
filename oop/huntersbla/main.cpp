#include <iostream>
#include <sstream>
#include "library/linsearch.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
/**

At every competition of the National Angling Championship, the results of the competitors were
recorded and put into a text file. Every line of the file contains the name of the angler the ID
of the competition (string without spaces), and the species and the size of the caught fishes
(pair of a string without spaces and a natural number). Data is separated by space or tab.
The lines of the file are ordered by the name of the anglers. The file is assumed to be in
the correct form. Sample line in the file:
PETER LAC0512 carp 45 carp 53 catfish 96
Give all those anglers who caught at least one carp on every competition he participated in and
give the weight of fishes they caught

*/

using namespace std;

struct Fish
{
    string name;
    int size_f;
    friend istream& operator>>(istream &is,Fish &f)
    {
        is >> f.name >> f.size_f;
        return is;
    }
};

struct output
{
    bool carbFound;
    int totalWeight;
}




class CarbSearch : public LinSearch<Fish,false>
{
    bool cond(const Fish& e) const override
    {
        return e.name == "carp";
    }
};

class calculateWeight : public Summation<Fish,int>
{
    int func(const Fish& e) const override { return e.size_f; }
    int neutral() const override {return 0; }
    int add( const int& a, const int& b) const override { return a+b; }

};


struct Contestant
{
    string person;
    string champ;
    bool caughtCarb;
    unsigned int totalWeights;
    friend istream& operator>>(istream &is,Contestant &c)
    {
        string line;
        getline(is,line,'\n');
        stringstream ss(line);
        ss >> c.person >> c.champ;
        StringStreamEnumerator<Fish> ssenor(ss);
        CarbSearch pr;
        calculateWeight pr2;
        pr.addEnumerator(&ssenor);
        pr2.addEnumerator(&ssenor);
        pr.run();
        pr2.run();
        c.caughtCarb = pr.found();
        c.totalWeights = pr2.result();
        cout<<c.totalWeights <<endl;
        return is;
    }
};

struct Result
{
    Result():totalFishWeights(0),name(""){ }
    Result(const string &n,unsigned int tW):name(n),totalFishWeights(tW){ }
    string name;
    unsigned int totalFishWeights;
};

class fishCalculations : public Summation<Contestant,Result>
{
public:
    fishCalculations(const string &contestantName) : _contestantName(contestantName) { }
private:
    Result func(const Contestant& e) const  override { return Result(e.person,e.totalWeights); }
    Result neutral() const override { return Result(); }
    Result add( const Result& a, const Result& b) const  override { return Result(b.name,a.totalFishWeights+b.totalFishWeights); }
    void first() override { }
    bool whileCond(const Contestant& current) const override { return current.person == _contestantName; }

    string _contestantName;
};


class ResultEnumerator : public Enumerator<Result>
{
private:
    SeqInFileEnumerator<Contestant>* _f;
    Result _result;
    bool _end;
    bool _empty;
public:
    ResultEnumerator(const string &fname): _empty(true) { _f = new SeqInFileEnumerator<Contestant>(fname); }
    ~ResultEnumerator() { delete _f; }
    void first() override { _f->first(); next(); if (!end()) _empty=false;}
    void next() override;
    Result current() const override { return _result; }
    bool end() const override { return _end; }
    bool getEmpty() const { return _empty; }
};

void ResultEnumerator::next()
{
    if (_end = _f->end()) return;
    _result.name = _f->current().person;
    fishCalculations pr(_result.name);
    pr.addEnumerator(_f);
    pr.run();
    _result = pr.result();
}

class Write : public Summation<Result,ostream>
{
public:
    Write(ostream *o):Summation<Result,ostream> (o) { }
    private:
    std::string func(const Result& e) const override
    {
        ostringstream oss(e.name);
        oss<<e.name<<","<<e.totalFishWeights<<"  : "<<endl;
        return oss.str();
    }
    bool cond(const Result& e) const override { return e.totalFishWeights >= 0; }
};


int main()
{
    try
    {
        ResultEnumerator enor("input.txt");
        if (enor.getEmpty()) cout << "There is none.\n";
        //else { cout<< pr.result().name << " " << pr.result().totalFishWeights  <<endl; }
        Write pr3(&cout);
        pr3.addEnumerator(&enor);
        pr3.run();
        if (enor.getEmpty()) cout << "There is none.\n";

    }
    catch (SeqInFileEnumerator<Contestant>::Exceptions err)
    {
        cerr<<"File not found!\n";
        return 1;
    }
    return 0;
}
