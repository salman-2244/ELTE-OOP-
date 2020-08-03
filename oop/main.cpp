#include <iostream>
#include <vector>
#include <fstream>
#include "hobbyani.h"
using namespace std;


void create(const string &str, vector<HobbyAnimal*> &animals, vector<Mood*> &mood)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}

    // population of the creatures
    int n; f >> n;
    animals.resize(n);
    for( int i=0; i<n; ++i ){
        char ani; string name; int exh;
        f >> ani >> name >> exh;
        switch(ani){
            case 'F' : animals[i] = new Fish(name, exh); break;
            case 'B' : animals[i] = new Bird(name, exh); break;
            case 'D' : animals[i] = new Dog(name, exh);   break;
        }
    }

    // population of the racetrack
    mood.resize(0);
    char m;
    while(f>>m) {
        switch(m){
            case 'o' : mood.push_back(Ordinary::instance());  break;
            case 'g' : mood.push_back(Good::instance()); break;
            case 'b' : mood.push_back(Bad::instance()); break;
        }
    }
}

bool allHappy(const vector<HobbyAnimal*> &animals)
{
    bool l = true;
    for(unsigned int i=0; l && i<animals.size(); i++){
      l = (animals[i]->alive() && animals[i]->happyAnimal());
    }
    return l;
}

bool anyAlive(const vector<HobbyAnimal*> &animals)
{
    bool l = false;
    for(unsigned int i=0; !l && i<animals.size(); i++){
      l = (animals[i]->alive());
    }
    return l;
}


void survivors(vector<HobbyAnimal*> &animals, vector<Mood*> &mood, vector <string> &min_alive) {
    int min_val=100;
    int min_ind=0;
    for( unsigned int j=0;j < mood.size(); j++ ) {
        if(allHappy(animals) ){
            mood[j] = mood[j]->increase();
        }

        for(unsigned int i=0; i < animals.size(); i++) {
            if(animals[i]->alive()){
                animals[i]->modifyMood(mood[j]);
            }
            std::cout<<animals[i]->getName()<<" "<<animals[i]->getExhil()<<std::endl;
        if(animals[i]->alive() && animals[i]->getExhil() < min_val){ // find minimum exhilaration
            min_val = animals[i]->getExhil();
            min_ind=i;
        }


        }
    }
        if(anyAlive(animals)){
            for(unsigned int i=0; i < animals.size(); i++) {
                if(animals[min_ind]->getExhil() == animals[i]->getExhil())
                    min_alive.push_back(animals[i]->getName()); //getting all minimum exhilaration names
            }
        }
}

void destroy(vector<HobbyAnimal*> &animals)
{
    for(auto animal : animals) delete animal;
}


void destroyMoods()
{
    Ordinary::destroy();
    Good::destroy();
    Bad::destroy();
}


#define NORMAL_MODE
#ifdef NORMAL_MOD

int main()
{
    vector<HobbyAnimal*> animals;
    vector<Mood*> mood;
    create("inp.txt", animals, mood);
    // Competition
    vector<string> alivemin;
    survivors(animals, mood, alivemin);
    cout<<endl;
    for(auto mini : alivemin) cout << "minimum: "<<mini << endl;

    destroy(animals);
    destroyMoods();


    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1","modifyMood,changeExhilaration")
{
    vector<HobbyAnimal*> animals;
    vector<Mood*> mood;
    vector<string> min_alive;

    min_alive.clear(); mood.clear();
    animals.push_back(new Fish("Nemo", 1));
    CHECK(animals[0]->alive() == true);
    mood.push_back(Bad::instance());
    animals[0]->modifyMood(mood[0]);
    CHECK(animals[0]->alive() == false);

    animals.clear();
    mood.clear();
    animals.push_back(new Dog("Minnie", 4));
    mood.push_back(Ordinary::instance()); mood.push_back(Ordinary::instance()); mood.push_back(Bad::instance());
    survivors(animals, mood, min_alive);

    CHECK(animals[0]->alive() == false);
    CHECK(mood[0] == Ordinary::instance());
    CHECK(mood[1] == Ordinary::instance());
    CHECK(mood[2] == Bad::instance());

    destroy(animals);


    animals.clear();
    mood.clear();
    animals.push_back(new Bird("Missy", 4));
    mood.push_back(Good::instance()); mood.push_back(Ordinary::instance()); mood.push_back(Bad::instance());
    survivors(animals, mood, min_alive);

    CHECK(animals[0]->alive() == true);
    CHECK(mood[0] == Good::instance());
    CHECK(mood[1] == Good::instance());
    CHECK(mood[2] == Ordinary::instance());

    destroy(animals);


    animals.clear();
    mood.clear();
    animals.push_back(new Fish("Ariel", 8));
    mood.push_back(Bad::instance()); mood.push_back(Bad::instance()); mood.push_back(Bad::instance());
    survivors(animals, mood, min_alive);

    CHECK(animals[0]->alive() == false);
    CHECK(mood[0] == Ordinary::instance());
    CHECK(mood[1] == Ordinary::instance());
    CHECK(mood[2] == Bad::instance());
    min_alive.clear();
    mood.clear();

    destroy(animals);

    animals.clear();
    mood.clear();
    animals.push_back(new Dog("Scooby", 3));
    mood.push_back(Good::instance()); mood.push_back(Bad::instance());
    survivors(animals, mood, min_alive);

    CHECK(animals[0]->alive() == true);
    CHECK(mood[0] == Good::instance());
    CHECK(mood[1] == Ordinary::instance());

    destroy(animals);


    animals.clear();
    mood.clear();
    animals.push_back(new Bird("Parry", 1));
    mood.push_back(Bad::instance()); mood.push_back(Good::instance());
    survivors(animals, mood, min_alive);

    CHECK(animals[0]->alive() == false);
    CHECK(mood[0] == Bad::instance());
    CHECK(mood[1] == Good::instance());
    min_alive.clear(); mood.clear();

    destroy(animals);
/*
    destroyMoods();
}


TEST_CASE("2", "length of interval") {
*/
//////////////////////////////////////////////////////////////////////

    create("inp11.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive.size() == 0);
    destroy(animals);
    min_alive.clear(); mood.clear();

    create("inp12.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive.size() == 1);
    destroy(animals);
    min_alive.clear(); mood.clear();

    create("inp13.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive.size() == 1);
    destroy(animals);
    min_alive.clear(); mood.clear();

    create("inp.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive.size() == 2);
    destroy(animals);
    min_alive.clear(); mood.clear();
/*
    destroyMoods();

}

TEST_CASE("3", "Outer Loops")
{
    vector<HobbyAnimal*> animals;
    vector<Mood*> mood;
    vector<string> min_alive;
*/


    create("inp21.txt", animals, mood);
    CHECK(allHappy(animals) == true);
    for(unsigned int i=0;i<animals.size();i++) {animals[i]->modifyMood(mood[0]);}
    CHECK(allHappy(animals) == true);
    destroy(animals);
    min_alive.clear(); mood.clear();

    create("inp22.txt", animals, mood);
    CHECK(allHappy(animals) == true);
    for(unsigned int i=0;i<animals.size();i++) {animals[i]->modifyMood(mood[0]);}
    CHECK(allHappy(animals) == false);
    destroy(animals);
    min_alive.clear(); mood.clear();
    animals.clear();

    create("inp23.txt", animals, mood);
    CHECK(anyAlive(animals) == false);
    for(unsigned int i=0;i<animals.size();i++) {animals[i]->modifyMood(mood[0]);}
    CHECK(anyAlive(animals) == false);
    destroy(animals);
    min_alive.clear(); mood.clear();


    create("inp12.txt", animals, mood);
    CHECK(anyAlive(animals) == true);
    survivors(animals, mood, min_alive);
    CHECK(anyAlive(animals) == true);
    destroy(animals);
    min_alive.clear(); mood.clear();
/*
    destroyMoods();
}

TEST_CASE("4. MinimumCheck") {
    vector<HobbyAnimal*> animals;
    vector<Mood*> mood;
    vector<string> min_alive;

*/

    animals.clear();
    create("inp31.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive[0] == "Minnie");
    destroy(animals);

   //no max element exists
    min_alive.clear(); mood.clear();
    create("inp32.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive.size() == 0);
    destroy(animals);

    animals.clear();
    min_alive.clear(); mood.clear();
    create("inp33.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive[0] == "Minnie");
    destroy(animals);

    animals.clear();
    min_alive.clear(); mood.clear();
    create("inp34.txt", animals, mood);
    survivors(animals, mood, min_alive);
    CHECK(min_alive[0] == "Minnie");
    destroy(animals);

    destroyMoods();
}

#endif
