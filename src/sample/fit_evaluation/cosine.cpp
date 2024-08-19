#include <math.h>
#include <vector>

#include "cosine.hpp"

#include "constants.hpp"

double eval_cosine_order__(double const & x, int const order){
    return cos(order*2*PI*x);
}

double naive_cosine(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_cosine_order__(x, i);
    }
    return val;
}