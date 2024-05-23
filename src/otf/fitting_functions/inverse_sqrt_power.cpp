#include <math.h>

#include "inverse_sqrt_power.hpp"

double eval_inverse_sqrt_power_order(double const & x, int const order){
    return pow(sqrt(x), -order);
}