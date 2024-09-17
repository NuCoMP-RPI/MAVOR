#include <math.h>
#include <vector>

#include "horner.hpp"
#include "clenshaw.hpp"

#include "coeff_exponential.hpp"

double exponential_alpha_recurrence__(double const & x, int const & k){
    return exp(x);
}

double exponential_beta_recurrence__(double const & x, int const & k){
    return 0;
}

double eval_exponential_order__(double const & x, int const order){
    return exp(order*x);
}

double naive_exponential_vec(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_exponential_order__(x, i);
    }
    return val;
}

double naive_exponential_iter(double const & x, Iter begin, Iter end) {
    double val = 0;
    int index = 0;
    for (auto it = begin; it != end; ++it, ++index) {
        val += *it * eval_exponential_order__(x, index);
    }
    return val;
}

double horner_exponential_custom_vec(double const & x, std::vector<double> const & coeffs){
    double exp_x = exp(x);
    double val = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i){
        val = val * exp_x + coeffs[i];
    }
    return val;
}

double horner_exponential_custom_iter(double const & x, Iter begin, Iter end) {
    double exp_x = std::exp(x);
    double val = 0;
    for (auto it = end; it != begin; ) {
        --it;
        val = val * exp_x + *it;
    }
    return val;
}

double horner_exponential_general_vec(double const & x, std::vector<double> const & coeffs){
    return horner(exp(x), coeffs);
}

double horner_exponential_general_iter(double const & x, Iter begin, Iter end) {
    return horner(std::exp(x), begin, end);
}

double clenshaw_exponential_custom_vec(double const & x, std::vector<double> const & coeffs) {
    double bk1 = 0;
    double bk = 0;
    double exp_x = exp(x);
    for (double k = coeffs.size(); k > 0; --k){
        bk = coeffs[k] + exp_x*bk1;
        bk1 = bk;
    }
    return coeffs[0] + exp_x*bk1;
}

double clenshaw_exponential_custom_iter(double const & x, Iter begin, Iter end) {
    double bk1 = 0;
    double bk = 0;
    double exp_x = std::exp(x);
    int size = std::distance(begin, end);
    for (int k = size - 1; k > 0; --k) {
        bk = *(begin + k) + exp_x * bk1;
        bk1 = bk;
    }
    return *begin + exp_x * bk1;
}

double clenshaw_exponential_general_vec(double const & x, std::vector<double> const & coeffs){
    return clenshaw(x, coeffs, exponential_alpha_recurrence__, exponential_beta_recurrence__, eval_exponential_order__);
}

double clenshaw_exponential_general_iter(double const & x, Iter begin, Iter end) {
    return clenshaw(x, begin, end, exponential_alpha_recurrence__, exponential_beta_recurrence__, eval_exponential_order__);
}