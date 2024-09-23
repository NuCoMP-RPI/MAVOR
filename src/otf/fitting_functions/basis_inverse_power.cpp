#include <math.h>

#include "basis_inverse_power.hpp"

double eval_inverse_power_order(double const & x, int const order){
    return pow(x, -order);
}