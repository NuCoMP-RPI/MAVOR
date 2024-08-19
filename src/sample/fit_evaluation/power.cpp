#include <math.h>
#include <vector>

#include "power.hpp"

double eval_power_order__(double const & x, int const order){
    return pow(x, order);
}

double naive_power(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_power_order__(x, i);
    }
    return val;
}