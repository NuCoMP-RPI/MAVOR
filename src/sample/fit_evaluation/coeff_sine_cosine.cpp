#include <math.h>
#include <vector>

#include "coeff_sine_cosine.hpp"

#include "constants.hpp"

std::vector<double> eval_sine_cosine_all_orders__(double const & x, int const max_order){
    std::vector<double> vals(max_order);
    double two_pi_x = 2*PI*x;
    vals[0] = 1;
    for (int i = 1; i < max_order; ++i){
        if (i%2 == 0) {vals[i] = sin(int(i/2)*two_pi_x);}
        else {vals[i] = cos(int(i/2)*two_pi_x);}
    }
    return vals;
}

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

double improved_sine_cosine(double const & x, std::vector<double> const & coeffs){
    std::vector<double> sine_cosine_points = eval_sine_cosine_all_orders__(x, coeffs.size());
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*sine_cosine_points[i];
    }
    return val;
}