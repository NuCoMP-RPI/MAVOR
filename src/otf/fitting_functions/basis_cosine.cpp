#include <math.h>

#include "basis_cosine.hpp"

#include "constants.hpp"

double eval_cosine_order(double const & x, int const order){
    return cos(order*2*PI*x);
}