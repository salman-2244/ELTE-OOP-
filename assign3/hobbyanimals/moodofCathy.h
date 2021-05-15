#ifndef MOODOFCATHY_H
#define MOODOFCATHY_H

#include <iostream>
#include <string>

class Dog;
class Fish;
class Bird;


class Mood
{
public:
    virtual void print() = 0;
    virtual Mood* modifyMood(Dog *p) = 0;
    virtual Mood* modifyMood(Bird *p) = 0;
    virtual Mood* modifyMood(Fish *p) = 0;
    virtual Mood* increase() = 0;
};

class Ordinary : public Mood
{
public:
    static Ordinary* instance();
    void print() override {std::cout<<"Ordinary"<<std::endl;};
    Mood* modifyMood(Dog *p) override;
    Mood* modifyMood(Bird *p) override;
    Mood* modifyMood(Fish *p) override;
    Mood* increase() override;
    static void destroy();

protected:
    Ordinary(){}
private:
    static Ordinary* _instance;

};


class Bad : public Mood
{
public:
    static Bad* instance();
    void print() override {std::cout<<"Bad"<<std::endl;};
    Mood* modifyMood(Fish *p) override;
    Mood* modifyMood(Dog *p) override;
    Mood* modifyMood(Bird *p) override;
    Mood* increase() override;
    static void destroy();
protected:
    Bad(){}
private:
    static Bad* _instance;


};

class Good : public Mood
{
public:
    static Good* instance();
    void print() override {std::cout<<"Good"<<std::endl;};
    Mood* modifyMood(Dog *p) override;
    Mood* modifyMood(Bird *p) override;
    Mood* modifyMood(Fish *p) override;
    Mood* increase() override;
    static void destroy();
protected:
    Good(){}
private:
    static Good* _instance;

};


#endif // MOODOFCATHY_H
