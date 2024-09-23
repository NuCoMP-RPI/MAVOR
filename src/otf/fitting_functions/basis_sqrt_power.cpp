#include <math.h>

#include "basis_sqrt_power.hpp"

double eval_sqrt_power_order(double const & x, int const order){
    return pow(sqrt(x), order);
}