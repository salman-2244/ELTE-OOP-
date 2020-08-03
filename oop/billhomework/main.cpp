#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> /** for reading input of varying length*/

using namespace std;

struct Bill
{
    string customer_name;
    string name;
    int unit_price;
    int counter;
    int Total() const;
    friend istream &operator>>(istream &is,Bill &bill);
    friend ostream &operator<<(ostream &os,const Bill &bill);
};

int Bill::Total() const
{
    int sum = 0;
    if(counter> 1)
    {
        sum += (unit_price* counter);
    }
    else{
        sum = unit_price;
    }
    return sum;
}

ostream &operator<<(ostream &os,const Bill &bill)
{
    os << bill.customer_name << " bought "<< bill.counter<< " " << bill.name << " item for " << bill.unit_price << " euro " <<endl;

    return os;
}

istream &operator>>(istream &is,Bill &bill) /// variable is has to be a stringstream
{
    is >> bill.customer_name>>bill.name>> bill.unit_price>>bill.counter;
    return is;
}

enum Status{norm,abnorm};

void open (ifstream &f); /// safe opening

template <typename Item>
void read(Status &st,Item &e, ifstream &f); /// reading operation for any type of data (template)

void calcTotal(ifstream &f); /// result calculation

int main()
{
    ifstream f;
    open(f);
    calcTotal(f);
    f.close();
    return 0;
}

void open(ifstream &f) /// safe opening
{
    do
    {
        cout << "File's name: ";
        string fname; /// = "data.txt";
        cin >> fname;
        f.open(fname.c_str());
    } while (f.fail());
}

template <typename Item>
void read(Status &st,Item &e,ifstream &f)
{
    string line;
    getline(f,line,'\n'); /// there is only one order's data in variable line
    if (f.fail() || line == "")
    {
        st = abnorm;
    }
    else
    {
        st = norm;
        stringstream ss(line); /// only one order
        ss >> e;
        ss.clear();
    }
}

void calcTotal(ifstream &f)
{
    int s = 0;
    Status st;
    Bill b;
    ///t.first
    read<Bill>(st,b,f); ///using template with concrete datatype: Item = Order
    //cout<< pizza_order;
    while (st==norm) ///!t.end
    {
        s += b.Total();/// s = s+...
        cout << "Total cost for "<< b.customer_name << " is " << s <<" euro " << endl;
        read<Bill>(st,b,f); ///next
        s = 0;
    }
}
