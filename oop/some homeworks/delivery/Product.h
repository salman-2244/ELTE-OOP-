#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <iostream>

class Product
{
public:
    Product(std::string adres) { address=adres; }
    std::string address;
};

#endif // PRODUCT_H_INCLUDED
