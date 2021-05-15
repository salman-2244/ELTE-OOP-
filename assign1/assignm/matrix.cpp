#include "Matrix.h"
#include <vector>
#include <iomanip>

using namespace std;


   Matrix::Matrix(int k)
   {
       if (k < 0) throw INVALID;
       _vec.clear();
       _vec.resize(k, 0);
   }

    Matrix::Matrix(const std::vector<int>& vec)
    {
        _vec = vec;

    }

    Matrix::Matrix(Matrix& mtx)
    {
        int sz = (mtx.get_size() * 3) - 2;
        _vec.resize(sz);
        for (int i = 0; i < sz; ++i) _vec[i] = mtx._vec[i];
    }

    Matrix& Matrix::operator=(const Matrix& mtx)
    {
        int s = (mtx.get_size() *3)-2;
        _resize(s);
        for (int i = 0; i < s; ++i) {
        _vec[i] = mtx._vec[i];
        }
        return *this;
    }

    void Matrix::_resize(int sz)
    {
            if (sz < 0) throw Matrix::INVALID;
            _vec.resize(sz, 0);

    }

    Matrix operator+(const Matrix& fst_mtx, const Matrix& snd_mtx)
    {
        int sz = fst_mtx.get_size();
        if (sz != snd_mtx.get_size()) throw Matrix::DIFFERENT;

        Matrix result((sz*3)-2);

        for (int i = 0; i < (sz*3)-1; ++i){
            result._vec[i] = fst_mtx._vec[i] + snd_mtx._vec[i];
        }
        return result;
    }

    Matrix operator*(const Matrix& fst_mtx, const Matrix& snd_mtx)
    {
        int sz = fst_mtx.get_size();
        if (sz != snd_mtx.get_size()) throw Matrix::DIFFERENT;
        Matrix result((sz * 3) - 2);

        for (int i = 0; i < sz; ++i)
        {
            for (int j = 0; j < sz; j++)
            {
                if (j == 0)
                {
                    for(int k = 0; k < sz; ++k)
                    {
                        result._vec[i] += fst_mtx(i, k) * snd_mtx(k, j);
                    }
                }
                else if (j == sz - 1)
                {
                    for(int k = 0; k < sz; ++k)
                    {
                        result._vec[sz + i] += fst_mtx(i, k) * snd_mtx(k, j);
                    }
                }
                else if (i == j && i != 0 && i != sz - 1)
                {
                    result._vec[sz * 2 + (i-1)] = fst_mtx(i, j) * snd_mtx(i, j);
                }
            }
        }
        //result._vec[i] = fst_mtx._vec[i] * snd_mtx._vec[i];
        return result;
    }


    std::ostream& operator<<(std::ostream& os, const Matrix& mtx)
    {
        int size = mtx.get_size();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                    os << setw(5) << mtx(i, j);
            }
            os << '\n';
        }

        return os;
    }

    istream& operator>>(istream& is, Matrix& mtx)
    {
        int s;
        is >> s;
        int vec_sz = (s * 3) - 2;
        mtx._resize(vec_sz);
        for (int i = 0; i < s; i++) {
            for (int j = 0; j <s; j++)
            {
                if (j==0 || j == s - 1 || (i == j && j != 0 && j != s - 1) )
                {
                    is >> mtx(i, j);
                }
            }
        }
        return is;
    }

    int Matrix::operator()(int i, int j) const
    {
        int _size = (_vec.size() +2) /3;
        if ((i >= _size || i < 0) || (j >= _size || j < 0)) throw OVERINDEXED;
        if (i != j && j != 0 && j != _size - 1) return 0;
        else {
            if (j == 0)
            {
                return _vec[i];
            }
            else if (j == _size - 1)
            {
                return _vec[_size + i];
            }
            else
            {
                return _vec[(_size * 2) + (i-1)];
            }
        }
    }

    int& Matrix::operator()(int i, int j)
    {
        int _size = (_vec.size() +2) /3;
        if ((i >= _size || i < 0) || (j >= _size || j < 0)) throw OVERINDEXED;
        if (i != j && j != 0 && j != _size - 1) throw NULLPART;
        else {
            if (j == 0)
            {
                return _vec[i];
            }
            else if (j == _size - 1)
            {
                return _vec[_size + i];
            }
            else
            {
                return _vec[(_size * 2) + (i-1)];
            }
        }
    }
