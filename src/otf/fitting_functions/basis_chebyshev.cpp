#include <iostream>

#include "basis_chebyshev.hpp"

double eval_chebyshev_order(double const & x, int const order){
    if (order<0) {throw std::range_error("Order must be a non-negative integer.");}
    
    switch (order)
    {
    case 0:
        return 1;

    case 1:
        return x;
    
    default:
        return 2*x*eval_chebyshev_order(x, order-1) - eval_chebyshev_order(x, order-2);
    }
}