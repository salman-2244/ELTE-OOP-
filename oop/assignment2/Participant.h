#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "Competition.h"
#include <string>

struct Participant {
    std::string id;
    bool sardineCaughter;
};

class ParticipantEnor
{
    private:
        CompetitionEnor _tt;
        Participant _current;
        bool _end;
    public:
        ParticipantEnor(const std::string &str): _tt(str) { };
        void first() {_tt.first(); next();}
        void next();
        Participant current() const { return _current;}
        bool end() const { return _end;}
};

#endif // PARTICIPANT_H
