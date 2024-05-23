#include <math.h>

#include "inverse_log_power.hpp"

double eval_inverse_log_power_order(double const & x, int const order){
    return pow(log(x), -order);
}