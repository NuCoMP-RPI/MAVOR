#include <math.h>

#include "sqrt_power.hpp"

double eval_sqrt_power_order(double const & x, int const order){
    return pow(sqrt(x), order);
}