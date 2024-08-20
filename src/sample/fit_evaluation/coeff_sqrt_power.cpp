#include <math.h>
#include <vector>

#include "coeff_sqrt_power.hpp"

double eval_sqrt_power_order__(double const & x, int const order){
    return pow(sqrt(x), order);
}

double naive_sqrt_power(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_sqrt_power_order__(x, i);
    }
    return val;
}