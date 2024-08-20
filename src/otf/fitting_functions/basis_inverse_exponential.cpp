#include <math.h>

#include "basis_inverse_exponential.hpp"

double eval_inverse_exponential_order(double const & x, int const order){
    return exp(-order*x);
}