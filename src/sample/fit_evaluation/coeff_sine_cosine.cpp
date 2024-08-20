#include <math.h>
#include <vector>

#include "coeff_sine_cosine.hpp"

#include "constants.hpp"

double eval_sine_cosine_order__(double const & x, int const order){
    if (order==0) {return 1;}
    else if (order%2 == 0) {return sin(int(order/2)*2*PI*x);}
    else {return cos(int(order/2)*2*PI*x);}
}

double naive_sine_cosine(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_sine_cosine_order__(x, i);
    }
    return val;
}