#include "Competition.h"

using namespace std;

myEnum::myEnum(const std::string &str)
{
     _f.open(str);
};

void myEnum::next()
{
    string line;
    getline(_f , line);
    if( !(_end = _f.fail()) ){
        istringstream is(line);
        is >> _cur.participant >> _cur.competition;
        _cur.sardineCaught = false;
        string fish;
        int size;
        for( is >> fish >> size ; !is.fail() && !_cur.sardineCaught; is >> fish >> size ){
            if(fish == "sardine") _cur.sardineCaught=true;
            else _cur.sardineCaught=false;
        }
    }
}
