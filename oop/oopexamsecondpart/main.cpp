#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/maxsearch.hpp"

/**
Each line of the file contains the name of a player (neither the given name nor the family name contain spaces),
the location of the game (a single word without spaces), then the data of shot attempts follow.
The data of one shot attempt consists of the time (minute and second, both are integer numbers) of the attempt,
the distance from the basket, and the score of the shot. The shot is worth 1, 2 or 3 points;
 0 points in case of missed shot.
In the first line of the sample, there are two successful and one missed shot; whereas
in the second line of the sample both the shots are successful.
The data in each line are separated by spaces. The file is sorted by the family name of players.


For grade 3: Determine a player who had at least two successful shots
(worth of 1, 2 or 3 points) in any of his games.
Print the name of the player along with the
location of the game and also the number of his successful shots in the given game.

For grade 5: Determine the player who obtained the most number of successful shots in total
in the 2020 season. Print the total number of successful shots the player obtained as well.

*/

using namespace std;

struct Shot
{
    int minute;
    int second;
    int distance;
    int score;
    friend istream& operator>>(istream &is, Shot &s) {  is>>s.minute>>s.second>>s.distance>>s.score; return is;}
};


class succesfulShots : public Summation<Shot,int>
{
    int func(const Shot& e) const override {return 1;}
    int neutral() const override {return 0;}
    int add( const int& a, const int& b) const override { return a+b; }
    bool cond(const Shot& e) const override { return e.score>0; }
};

struct Player{
    string name;
    string surname;
    string location;
    int n_good_shots;
    friend istream& operator>>(istream &is, Player &p)
    {
        string line;
        getline (is,line,'\n');
        stringstream ss(line);
        ss>>p.name>>p.surname>>p.location;
        StringStreamEnumerator<Shot> ssenor(ss);
        succesfulShots pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        p.n_good_shots = pr.result();
        return is;
    }

};

class MySearch : public LinSearch<Player,false>
{
    bool cond(const Player& e) const override { return e.n_good_shots>=2;}
};

class TotalShots : public Summation<Player, int>
{
private:
    string _name;
public:
    TotalShots(const string &name) : _name(name) {}
protected:
    int func(const Player &p) const override { return p.n_good_shots; }
    int neutral() const override { return  0; }
    int add(const int &a, const int &b) const override { return a+b; }
    bool whileCond(const Player &p) const override { return p.name == _name; }
    void first() override {}
};


class FreqEnumerator : public Enumerator<Player>
{
private:
    SeqInFileEnumerator<Player>* _f;
    Player _freq;
    bool _end;
public:
    FreqEnumerator(const string &fname) { _f = new SeqInFileEnumerator<Player>(fname); }
    ~FreqEnumerator() { delete _f; }
    void first() override { _f->first(); next(); }
    void next() override;
    Player current() const override { return _freq; }
    bool end() const override { return _end; }
};

void FreqEnumerator::next()
{
    if((_end = _f->end())) return;
    _freq.name = _f->current().name;
    TotalShots pr(_freq.name);
    pr.addEnumerator(_f);

    pr.run();
    _freq.n_good_shots = pr.result();
}


class mostShots : public MaxSearch<Player,int>
{
protected:
    int func(const Player &e) const override { return e.n_good_shots; }
};


int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "test3.txt";
        SeqInFileEnumerator<Player> enor(filename);
        MySearch pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found()) cout << pr.elem().name << " from " << pr.elem().location << " with " << pr.elem().n_good_shots << " good shots.\n";
        else { cout<< "There aren't any person who has more than 2 successful shots." <<endl; }

        mostShots pr2;
        FreqEnumerator myenor("test3.txt");
        pr2.addEnumerator(&myenor);

        pr2.run();
        if (pr2.found())
            cout << pr2.optElem().name << " has most succesful shots during season with "<< pr2.optElem().n_good_shots <<" shots. \n";

    }
    catch(SeqInFileEnumerator<Player>::Exceptions e)
    {
        cout<<"That isn't a file!!!!\n";
        return 1;
    }

    return 0;
}
