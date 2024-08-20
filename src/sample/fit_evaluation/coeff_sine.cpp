#include <math.h>
#include <vector>

#include "coeff_sine.hpp"

#include "constants.hpp"

double eval_sine_order__(double const & x, int const order){
    if (order==0) {return 1;}
    return sin(order*2*PI*x);
}

double naive_sine(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_sine_order__(x, i);
    }
    return val;
}