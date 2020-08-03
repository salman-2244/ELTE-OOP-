#include <iostream>
#include <sstream>
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"


using namespace std;

struct Data
{
    string subject;
    int grade;
    friend istream& operator>>(istream &is, Data &d)
    {
        is >> d.subject >> d.grade;
        return is;
    }
};

class mySearch : public LinSearch<Data,true>
{
    bool cond(const Data& d) const override
    {
        return d.grade>=2;
    }

};



struct Student
{
    string name;
    string school;
    bool passedAll;
    friend istream& operator>>(istream &is, Student &r)
    {
        string line;
        getline(is,line,'\n');
        stringstream ss(line);
        ss >> r.name >> r.school;
        StringStreamEnumerator<Data> ssenor(ss);
        mySearch pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        r.passedAll = pr.found();
    }

};


class findSearch : public LinSearch<Student,false>
{

    bool cond(const Student& e) const override
    {
        return e.passedAll;
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
            filename="empty.txt";
        SeqInFileEnumerator<Student> enor(filename);
        findSearch pr;
        pr.addEnumerator(&enor);
        pr.run();
        if(pr.found()) { cout<< pr.elem().name << endl; }
        else {cout<<"No student could"<<'\n';}
    }
    catch(SeqInFileEnumerator<Student>::Exceptions err)
    {
        cout<<"File not found"<<endl;
        return 1;
    }
    return 0;
}
