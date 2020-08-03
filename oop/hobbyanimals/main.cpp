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
            mood[j]->print();
        }

        for(unsigned int i=0; i < animals.size(); i++) {
            if(animals[i]->alive()){
                animals[i]->modifyMood(mood[j]);
            }
            std::cout<<animals[i]->getName()<<" "<<animals[i]->getExhil()<<std::endl;
            if(!animals[min_ind]->alive())
            {
                min_val=100;
            }
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
//#ifdef NORMAL_MOD

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
