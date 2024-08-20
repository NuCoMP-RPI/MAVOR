#include <math.h>
#include <vector>

#include "coeff_log_power.hpp"

double eval_log_power_order__(double const & x, int const order){
    return pow(log(x), order);
}

double naive_log_power(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_log_power_order__(x, i);
    }
    return val;
}