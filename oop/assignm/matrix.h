#pragma once
#include <iostream>
#include <vector>
class Matrix
{
public:
    enum Exceptions{ OVERINDEXED, NULLPART, DIFFERENT, INVALID };
    Matrix(int k);
    Matrix(){ _vec.clear(); };
    Matrix(const std::vector<int>& vec);
    Matrix(Matrix& mtx);
    ~Matrix() { }
    int get_size() const { return (_vec.size()+2) /3;}

    int operator()(int i, int j) const;
    int& operator()(int i, int j);

    Matrix& operator=(const Matrix& mtx);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mtx);
    friend std::istream& operator>>(std::istream& is, Matrix& mtx);
    friend Matrix operator+(const Matrix& fst_mtx,const Matrix& snd_mtx);
    friend Matrix operator*(const Matrix& fst_mtx, const Matrix& snd_mtx);



private:
    std::vector<int> _vec;
    void _resize(int sz);

};
