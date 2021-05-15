#include "Participant.h"

void ParticipantEnor::next()
{
    if( !(_end = _tt.end()) ){
        _current.id = _tt.current().participant;
        _current.sardineCaughter = _tt.current().sardineCaught;
        for( ; !_tt.end() && _tt.current().participant == _current.id; _tt.next() ){
            _current.sardineCaughter = _current.sardineCaughter && (_tt.current().sardineCaught);
        }
    }
}

