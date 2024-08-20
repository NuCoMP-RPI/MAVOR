#include <math.h>
#include <vector>

#include "coeff_exponential.hpp"

double eval_exponential_order__(double const & x, int const order){
    return exp(order*x);
}

double naive_exponential(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_exponential_order__(x, i);
    }
    return val;
}