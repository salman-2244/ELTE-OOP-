#include <iostream>
#include <vector>
#include <sstream>
#include "library/maxsearch.hpp"
#include "library/summation.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"




using namespace std;

struct Sport
{
    string sname;
    int place;
    friend istream& operator>>(istream &is, Sport &s);
};

istream& operator>>(istream &is, Sport &s)
{
    is >> s.sname >> s.place;
    return is;
}


struct Result{
    int bestRank;
    bool highJump;
    int noOfSilver;
    Result() {}
    Result(int bR,bool hJ,int s) : bestRank(bR), highJump(hJ), noOfSilver(s) {}
};


class Calculation : public Summation<Sport,Result>
{
public:
    Result func(const Sport& s) const override
    {
        return Result(s.place,s.sname=="highjump",s.place==2 ? 1 : 0);
    }
    Result neutral() const override
    {
        return Result(9999,false,0);
    }
    Result add( const Result& a, const Result& b) const override
    {
        return Result(a.bestRank < b.bestRank ? a.bestRank : b.bestRank, a.highJump || b.highJump, a.noOfSilver + b.noOfSilver);
    };

};

struct Participant
{
    string name;
    string school_id;
    int bestRank;
    bool highJump;
    int noOfSilver;
    friend istream& operator>>(istream &is, Participant &p)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss >> p.name>>p.school_id; ///in is, there are only marks
        StringStreamEnumerator<Sport> ssenor(ss);
        Calculation pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        p.bestRank = pr.result().bestRank;
        p.highJump = pr.result().highJump;
        p.noOfSilver = pr.result().noOfSilver;
        return is;
    }
};

class mySearch : public LinSearch<Participant,false>
{
    bool cond(const Participant& p) const override
    {
        return p.highJump && p.bestRank==2;
    }
};

int main(int argc,char** argv)
{
    try
    {
        string filename;
        if (argc > 1)
            filename=argv[1];
        else
            filename="input.txt";
        SeqInFileEnumerator<Participant> enor(filename);
        mySearch pr;
        pr.addEnumerator(&enor);
        pr.run();
        if(pr.found()) { cout<< pr.elem().name << " " << pr.elem().school_id << " " << pr.elem().noOfSilver<< endl; }
    }
    catch(SeqInFileEnumerator<Participant>::Exceptions err)
    {
        cout<<"File not found"<<endl;
        return 1;
    }


    return 0;
}
