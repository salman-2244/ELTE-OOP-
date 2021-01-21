#include "myMenu.h"

using namespace std;

    void myMenu::readMatrix()
    {
        try
        {
            cout << "Give the size and the items of the matrix: ";
            cin >> fst_mtx;
        }
        catch (Matrix::Exceptions ex)
        {
            if (ex == Matrix::INVALID)
                cout << "Invalid size!" << endl;
            else
                cout << "Unhandled ecxeption!" << endl;
        }



    }


    void myMenu::showMenu()
    {
        cout << endl << endl;
        cout << " 0.Quit" << endl;
        cout << " 1.Get an element of the matrix" << endl;
        cout << " 2.Read matrix" << endl;
        cout << " 3.Add matrices" << endl;
        cout << " 4.Multiply matrices" << endl;
        cout << " 5.Print matrices" << endl;
        cout << " 6.Overwrite an element of matrix" << endl;


    }
    void myMenu::executeMenu()
    {
        showMenu();
        int n=0;
        do
        {

            cout << "Please enter an integer: " << endl;
            cin >> n;
            switch (n)
            {
            case 1:
                getIndices();
                break;

            case 2:
                readMatrix();
                break;
            case 3:
                sumMatrices();
                break;
            case 4:
                multMatrices();
                break;
            case 5:
                printOutMtx();
                break;
            case 6:
                setIndices();
                break;
            }

        } while (n != 0);
    }
    void myMenu::getIndices() const
    {
        try
        {
            int i, j;
            cout << "Give the index of the row: ";
            cin >> i;
            cout << "Give the index of the column: ";
            cin >> j;
            {
                cout << "fst_mtx[" << i << "," << j << "]= " << fst_mtx(i - 1, j - 1) << endl;
            }
        }
        catch (Matrix::Exceptions ex)
        {
            if (ex == Matrix::OVERINDEXED)
                cout << "Overindexing!" << endl;
            else
                cout << "Unhandled exception!" << endl;
        }

    }

    void myMenu::setIndices()
    {
        int i,j,e;
        cout << "Give the index of the row: ";
        cin >> i;
        cout << "Give the index of the column: ";
        cin >> j;
        cout << "Give the value: ";
        cin >> e;
        try
        {
            fst_mtx(i-1,j-1) = e;
        }
        catch(Matrix::Exceptions ex)
        {
            if(ex == Matrix::OVERINDEXED)
                cout << "Overindexing!" << endl;
            if (ex == Matrix::NULLPART)
                cout << "These indexes do not point to the diagonal!" << endl;
    }
}


    void myMenu::sumMatrices()
    {
        try {
            cout << "Please enter size for second matrix and elements for the second matrix: " << endl;
            Matrix snd_mtx;

            cout << "Give the size and the items of the second  matrix: " << endl;
            cin >> snd_mtx;
            cout << "Sum of the matrices: " << endl;
            cout << fst_mtx + snd_mtx  <<endl;
        }
        catch(Matrix::Exceptions ex)
        {
            if (ex == Matrix::INVALID)
                cout << "Invalid size!" << endl;
            if (ex == Matrix::DIFFERENT)
                cout << "Different sizes!" << endl;
        }

    }
    void myMenu::multMatrices()
    {
        try
        {
            Matrix snd_mtx;

            cout << "Give the size and the items of the second  matrix: " << endl;
            cin >> snd_mtx;
            cout << "Multiplication of the matrices: " << endl;
            cout << fst_mtx * snd_mtx << endl;
        }
        catch(Matrix::Exceptions ex)
        {
            if(ex == Matrix::INVALID)
                cout << "Invalid size!" << endl;
            if(ex == Matrix::DIFFERENT)
                cout << "Different sizes!" << endl;
        }

    }
    void myMenu::printOutMtx()
    {
        cout << fst_mtx << endl;
    }
