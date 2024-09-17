#include <math.h>
#include <vector>
#include <iterator>

#include "coeff_cosine.hpp"

#include "constants.hpp"

double eval_cosine_order__(double const & x, int const order){
    return cos(order*2*PI*x);
}

std::vector<double> eval_cosine_all_orders__(double const & x, int const max_order){
    std::vector<double> vals(max_order);
    double two_pi_x = 2*PI*x;
    for (int i = 0; i < max_order; ++i){
        vals[i] = cos(i*two_pi_x);
    }
    return vals;
}

double naive_cosine_vec(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_cosine_order__(x, i);
    }
    return val;
}

double naive_cosine_iter(double const & x, Iter begin, Iter end) {
    double val = 0;
    int index = 0;
    for (auto it = begin; it != end; ++it, ++index) {
        val += *it * eval_cosine_order__(x, index);
    }
    return val;
}

double improved_cosine_vec(double const & x, std::vector<double> const & coeffs){
    std::vector<double> cosine_points = eval_cosine_all_orders__(x, coeffs.size());
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*cosine_points[i];
    }
    return val;
}

double improved_cosine_iter(double const & x, Iter begin, Iter end) {
    int size = std::distance(begin, end);
    std::vector<double> cosine_points = eval_cosine_all_orders__(x, size);
    double val = 0;
    int index = 0;
    for (auto it = begin; it != end; ++it, ++index) {
        val += *it * cosine_points[index];
    }
    return val;
}