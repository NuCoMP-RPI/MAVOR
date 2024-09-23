#include <math.h>

#include "basis_exponential.hpp"

double eval_exponential_order(double const & x, int const order){
    return exp(order*x);
}