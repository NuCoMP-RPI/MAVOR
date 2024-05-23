#include <iostream>

#include "legendre.hpp"

double eval_legendre_order(double const & x, int const order){
    if (order<0) {throw std::range_error("Order must be a non-negative integer.");}
    
    switch (order)
    {
    case 0:
        return 1;

    case 1:
        return x;
    
    default:
        return ((2*order - 1)*x*eval_legendre_order(x, order-1) - (order-1)*eval_legendre_order(x, order-2))/order;
    }
}