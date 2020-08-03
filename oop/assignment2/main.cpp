#include <iostream>
#include "Participant.h"

using namespace std;


// Searching for a participant who caught sardine in all championships he participated
bool search(const string &name, string &id)
{
    ParticipantEnor t(name);
    bool l = false;
    for(t.first(); !l && !t.end(); t.next()){
        l = t.current().sardineCaughter;
        id = t.current().id;
    }
    return l;
}

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    string id;
    if(search("input.txt", id)) cout << id << " is a";
    else cout << "there is no";
    cout << " Sardine caughter.\n";
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// linear search
TEST_CASE("empty file", "emp.txt") {
    string id;
    CHECK_FALSE(search("emp.txt", id));
}

TEST_CASE("1 participant", "one.txt") {
    string id;
    CHECK(search("one.txt", id));
}

TEST_CASE("more participants more contests", "more.txt") {
    string id;
    CHECK(search("more.txt", id));
}

TEST_CASE("first participant is sardine caughter", "input.txt") {
    string id;
    CHECK(search("input.txt", id));
}

TEST_CASE("last participant is sardine caughter", "onlylast.txt") {
    string id;
    CHECK(search("onlylast.txt", id));
}

TEST_CASE("one sardine caughter among more anglers more contests ", "morecontests1caughter.txt") {
    string id;
    CHECK(search("morecontests1caughter.txt", id));
}

TEST_CASE("no sardine caughter participants more contests ", "morecontnocaughter.txt") {
    string id;
    CHECK_FALSE(search("morecontnocaughter.txt", id));
}

TEST_CASE("more sardine caughter participants more contests ", "morecontmorecaught.txt") {
    string id;
    CHECK(search("morecontmorecaught.txt", id));
}

// optimistic linear search

TEST_CASE("no contest", "emp.txt") {
    ParticipantEnor t("emp.txt");
    t.first();
    CHECK(t.current().sardineCaughter);
}

TEST_CASE("1 participant 1 competition", "one.txt") {
    ParticipantEnor t("one.txt");
    t.first();
    CHECK(t.current().sardineCaughter);
}

TEST_CASE("1 participant more contests", "t3.txt") {
    ParticipantEnor t("t3.txt");
    t.first();
    CHECK_FALSE(t.current().sardineCaughter);
}

TEST_CASE("1 participant did not catch sardines on his first contest", "nosardineonfirst.txt") {
    ParticipantEnor t("nosardineonfirst.txt");
    t.first();
    CHECK_FALSE(t.current().sardineCaughter);
}

TEST_CASE("1 participant did not catch sardines on his last contest", "nosardineatlast.txt") {
    ParticipantEnor t("nosardineatlast.txt");
    t.first();
    CHECK_FALSE(t.current().sardineCaughter);
}

TEST_CASE("first angler did not catch any sardines", "onlylast.txt") {
    ParticipantEnor t("onlylast.txt");
    t.first();
    CHECK_FALSE(t.current().sardineCaughter);
}

TEST_CASE("first angler caught catfish on only one competition", "onlyfirst.txt") {
    ParticipantEnor t("onlyfirst.txt");
    t.first();
    CHECK_FALSE(t.current().sardineCaughter);
}

TEST_CASE("the first angler is skillful", "input.txt") {
    ParticipantEnor t("input.txt");
    t.first();
    CHECK(t.current().sardineCaughter);
}

// decision


TEST_CASE("no catch", "nosardine.txt") {
    CompetitionEnor tt("nosardine.txt");
    tt.first();
    CHECK(tt.current().sardineCaught == 0);
}

TEST_CASE("with catch", "input.txt") {
    CompetitionEnor tt("input.txt");
    tt.first();
    CHECK(tt.current().sardineCaught == 1);
}

TEST_CASE("more catches", "morecatches.txt") {
    CompetitionEnor tt("morecatches.txt");
    tt.first();
    CHECK(tt.current().sardineCaught == 1);
}

TEST_CASE("first catch is sardine", "morecatches.txt") {
    CompetitionEnor tt("morecatches.txt");
    tt.first();
    CHECK(tt.current().sardineCaught == 1);
}

TEST_CASE("last catch is sardine", "morecontmorecaught.txt") {
    CompetitionEnor tt("morecontmorecaught.txt");
    tt.first();
    CHECK(tt.current().sardineCaught == 1);
}

TEST_CASE("no catfish", "nosardine.txt") {
    CompetitionEnor tt("nosardine.txt");
    tt.first();
    CHECK(tt.current().sardineCaught == 0);
}


#endif
