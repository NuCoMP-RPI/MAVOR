#include <math.h>
#include <vector>

#include "coeff_sine.hpp"

#include "constants.hpp"

std::vector<double> eval_sine_all_orders__(double const & x, int const max_order){
    std::vector<double> vals(max_order);
    double two_pi_x = 2*PI*x;
    vals[0] = 1;
    for (int i = 1; i < max_order; ++i){
        vals[i] = sin(i*two_pi_x);
    }
    return vals;
}

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

double improved_sine(double const & x, std::vector<double> const & coeffs){
    std::vector<double> sine_points = eval_sine_all_orders__(x, coeffs.size());
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*sine_points[i];
    }
    return val;
}