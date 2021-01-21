#ifndef HOBBYANI_H_INCLUDED
#define HOBBYANI_H_INCLUDED

#include "moodofCathy.h"

class HobbyAnimal{
protected:
    std::string _name;
    int _exh;
    HobbyAnimal (const std::string &str, int e = 0) :_name(str), _exh(e) {}
public:
    std::string getName() const { return _name; }
    int getExhil()const { return _exh;}
    bool happyAnimal()const { return _exh>=5;}
    bool alive() const { return _exh >= 0; }
    void changeExhilaration(int e) { _exh += e; }
    virtual void modifyMood(Mood* &mood) = 0;
    virtual ~HobbyAnimal () {}
};

class Fish : public HobbyAnimal {
public:
    Fish(const std::string &str, int e = 0) : HobbyAnimal(str, e){}
    void modifyMood(Mood* &mood) override {
        mood = mood->modifyMood(this);
    }
};

// class of Dune beetles
class Dog : public HobbyAnimal {
public:
    Dog(const std::string &str, int e = 0) : HobbyAnimal(str, e){}
    void modifyMood(Mood* &mood) override {
        mood = mood->modifyMood(this);
    }
};

class Bird : public HobbyAnimal {
public:
    Bird(const std::string &str, int e = 0) : HobbyAnimal(str, e){}
    void modifyMood(Mood* &mood) override{
        mood = mood->modifyMood(this);
    }
};


#endif // HOBBYANI_H_INCLUDED
