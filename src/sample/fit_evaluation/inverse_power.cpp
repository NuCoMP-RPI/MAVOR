#include <math.h>
#include <vector>

#include "inverse_power.hpp"

double eval_inverse_power_order__(double const & x, int const order){
    return pow(x, -order);
}

double naive_inverse_power(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_inverse_power_order__(x, i);
    }
    return val;
}