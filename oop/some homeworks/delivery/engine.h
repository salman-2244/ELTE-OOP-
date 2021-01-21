#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <iostream>

class Engine
{
public:
    Engine() : _isRunning(false){};
    void start() { _isRunning=true; std::cout<< "engine started \n "; }
    void stop() {_isRunning=false; std::cout<< "engine stopped \n "; }
    bool isRunning() const { return _isRunning; }
private:
    bool _isRunning;

};


#endif // ENGINE_H_INCLUDED
