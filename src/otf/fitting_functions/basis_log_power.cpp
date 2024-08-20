#include <math.h>

#include "basis_log_power.hpp"

double eval_log_power_order(double const & x, int const order){
    return pow(log(x), order);
}