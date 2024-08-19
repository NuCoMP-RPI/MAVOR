#include <math.h>
#include <vector>

#include "inverse_exponential.hpp"

double eval_inverse_exponential_order__(double const & x, int const order){
    return exp(-order*x);
}

double naive_inverse_exponential(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_inverse_exponential_order__(x, i);
    }
    return val;
}