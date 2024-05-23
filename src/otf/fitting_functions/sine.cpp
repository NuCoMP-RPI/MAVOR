#include <math.h>

#include "sine.hpp"

#include "constants.hpp"

double eval_sine_order(double const & x, int const order){
    if (order==0) {return 1;}
    return sin(order*2*PI*x);
}