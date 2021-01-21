#include "moodofCathy.h"
#include "hobbyani.h"


Ordinary* Ordinary::_instance = nullptr;
Ordinary* Ordinary::instance()
{
    if(_instance == nullptr) {
        _instance = new Ordinary();
    }
    return _instance;
}

Mood* Ordinary::increase()
{
    return Good::instance();
}

Mood* Ordinary::modifyMood(Fish *p)
{
    p->changeExhilaration(-3);
    return this;
}

Mood* Ordinary::modifyMood(Bird *p)
{
    p->changeExhilaration(-1);
    return this;
}

Mood* Ordinary::modifyMood(Dog *p)
{
    p->changeExhilaration(0);
    return this;
}
void Ordinary::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}


Good* Good::_instance = nullptr;
Good* Good::instance()
{
    if(_instance == nullptr) {
        _instance = new Good();
    }
    return _instance;
}

Mood* Good::increase()
{
    return this;
}

Mood* Good::modifyMood(Fish *p)
{
    p->changeExhilaration(1);
    return this;
}

Mood* Good::modifyMood(Bird *p)
{
    p->changeExhilaration(2);
    return this;
}

Mood* Good::modifyMood(Dog *p)
{
    p->changeExhilaration(3);
    return this;
}
void Good::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}

Bad* Bad::_instance = nullptr;
Bad* Bad::instance()
{
    if(_instance == nullptr) {
        _instance = new Bad();
    }
    return _instance;
}

Mood* Bad::increase()
{
    return Ordinary::instance();
}

Mood* Bad::modifyMood(Fish *p)
{
    p->changeExhilaration(-5);
    return this;
}

Mood* Bad::modifyMood(Bird *p)
{
    p->changeExhilaration(-3);
    return this;
}

Mood* Bad::modifyMood(Dog *p)
{
    p->changeExhilaration(-10);
    return this;
}
void Bad::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}

