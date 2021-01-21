#include <iostream>
#include <fstream>
#include "myMenu.h"
#include "Matrix.h"


using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{

    myMenu menu;

    menu.executeMenu();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>

TEST_CASE("create", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix mtx;
    in >> mtx; // 3
    CHECK(mtx(0,0) == 1);
    CHECK(mtx(0,2) == 2);
    CHECK(mtx(1,0) == 3);
    CHECK(mtx(1,1) == 4);
    CHECK(mtx(1,2) == 5);
    CHECK(mtx(2,0) == 6);
    CHECK(mtx(2,2) == 7);

    Matrix snd_mtx;
    in >> snd_mtx; // 2
    CHECK(snd_mtx(0,0) == 1);
    CHECK(snd_mtx(0,1) == 2);
    CHECK(snd_mtx(1,0) == 3);
    CHECK(snd_mtx(1,1) == 4);

    Matrix third;
    in >> third; // 1
    CHECK(third(0,0)==4);
}

TEST_CASE("getting and changing an element of the matrix", "")
{
    Matrix a(4);
    CHECK(a(0,0) == 0);
    a(0,0) = 2;
    CHECK(a(0,0) == 2);
}


TEST_CASE("copy constructor", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a;
    in >> a; // 3
    Matrix b = a;

    CHECK(a(0,0) == b(0,0));
    CHECK(a(0,2) == b(0,2));
    CHECK(a(1,0) == b(1,0));
    CHECK(a(1,1) == b(1,1));
    CHECK(a(1,2) == b(1,2));
    CHECK(a(2,0) == b(2,0));
    CHECK(a(2,2) == b(2,2));
}

TEST_CASE("assignment operator", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix mtx, snd_mtx; // 3
    in >> mtx;

    snd_mtx = mtx; // check every non-zero item
    CHECK(mtx(0,0) == snd_mtx(0,0));
    CHECK(mtx(0,2) == snd_mtx(0,2));
    CHECK(mtx(1,0) == snd_mtx(1,0));
    CHECK(mtx(1,1) == snd_mtx(1,1));
    CHECK(mtx(1,2) == snd_mtx(1,2));
    CHECK(mtx(2,0) == snd_mtx(2,0));
    CHECK(mtx(2,2) == snd_mtx(2,2));

    Matrix third; // 3
    third = snd_mtx = mtx; // check every non-zero item
    CHECK(mtx(0,0) == third(0,0));
    CHECK(mtx(0,2) == third(0,2));
    CHECK(mtx(1,0) == third(1,0));
    CHECK(mtx(1,1) == third(1,1));
    CHECK(mtx(1,2) == third(1,2));
    CHECK(mtx(2,0) == third(2,0));
    CHECK(mtx(2,2) == third(2,2));

    mtx = mtx; // check every non-zero item
    CHECK(mtx(0,0) == 1);
    CHECK(mtx(0,2) == 2);
    CHECK(mtx(1,0) == 3);
    CHECK(mtx(1,1) == 4);
    CHECK(mtx(1,2) == 5);
    CHECK(mtx(2,0) == 6);
    CHECK(mtx(2,2) == 7);
}

TEST_CASE("add", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b, c, d, f, e, z; // 3
    in >> a >> b >> z >> e;

    c = a + b; // check every non-zero item
    CHECK(c(0,0) == 4);
    CHECK(c(0,2) == 5);
    CHECK(c(1,0) == 6);
    CHECK(c(1,1) == 7);
    CHECK(c(1,2) == 8);
    CHECK(c(2,0) == 9);
    CHECK(c(2,2) == 10);

    d = b + a; // check every non-zero item
    CHECK(c(0,0) == d(0,0));
    CHECK(c(0,2) == d(0,2));
    CHECK(c(1,0) == d(1,0));
    CHECK(c(1,1) == d(1,1));
    CHECK(c(1,2) == d(1,2));
    CHECK(c(2,0) == d(2,0));
    CHECK(c(2,2) == d(2,2));

    d = (a + b) + c;
    f = a + (b + c); // check every non-zero item
    CHECK(d(0,0) == f(0,0));
    CHECK(d(0,2) == f(0,2));
    CHECK(d(1,0) == f(1,0));
    CHECK(d(1,1) == f(1,1));
    CHECK(d(1,2) == f(1,2));
    CHECK(d(2,0) == f(2,0));
    CHECK(d(2,2) == f(2,2));

    c = a + z; // check every non-zero item
    CHECK(c(0,0) == a(0,0));
    CHECK(c(0,2) == a(0,2));
    CHECK(c(1,0) == a(1,0));
    CHECK(c(1,1) == a(1,1));
    CHECK(c(1,2) == a(1,2));
    CHECK(c(2,0) == a(2,0));
    CHECK(c(2,2) == a(2,2));
}


TEST_CASE("multiply", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b, c, d, f, e, z; // 3
    in >> a >> b >> z >> e;

    c = a * b;
    CHECK(c(0,0) == 21);
    CHECK(c(0,2) == 27);
    CHECK(c(1,0) == 30);
    CHECK(c(1,1) == 12);
    CHECK(c(1,2) == 42);
    CHECK(c(2,0) == 21);
    CHECK(c(2,2) == 27);

    d = b * a; // for N matrix a*b != b*a  except diagonal!!!
    CHECK(c(0,0) != d(0,0));
    CHECK(c(0,2) != d(0,2));
    CHECK(c(1,0) != d(1,0));
    CHECK(c(1,1) == d(1,1));
    CHECK(c(1,2) != d(1,2));
    CHECK(c(2,0) != d(2,0));
    CHECK(c(2,2) != d(2,2));

    d = (a * b) * c;
    f = a * (b * c);
    CHECK(d(0,0) == f(0,0));
    CHECK(d(0,2) == f(0,2));
    CHECK(d(1,0) == f(1,0));
    CHECK(d(1,1) == f(1,1));
    CHECK(d(1,2) == f(1,2));
    CHECK(d(2,0) == f(2,0));
    CHECK(d(2,2) == f(2,2));

    c = a * z;
    CHECK(c(0,0) == 0);
    CHECK(c(0,2) == 0);
    CHECK(c(1,0) == 0);
    CHECK(c(1,1) == 0);
    CHECK(c(1,2) == 0);
    CHECK(c(2,0) == 0);
    CHECK(c(2,2) == 0);
}


TEST_CASE("exceptions", "")
{

    Matrix a(3);

    try
    {
        a(3,3) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    try
    {
        a(-1,4) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    Matrix b(2);
    Matrix c(3);

    try
    {
        a = b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        c = a + b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        c = a * b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }


}

#endif
