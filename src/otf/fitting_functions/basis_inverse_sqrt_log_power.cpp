#include <math.h>

#include "basis_inverse_sqrt_log_power.hpp"

double eval_inverse_sqrt_log_power_order(double const & x, int const order){
    return pow(sqrt(log(x)), -order);
}