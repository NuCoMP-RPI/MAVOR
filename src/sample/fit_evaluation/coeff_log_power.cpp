#include <math.h>
#include <vector>

#include "horner.hpp"
#include "clenshaw.hpp"

#include "coeff_log_power.hpp"

double log_power_alpha_recurrence__(double const & x, int const & k){
    return log(x);
}

double log_power_beta_recurrence__(double const & x, int const & k){
    return 0;
}

double eval_log_power_order__(double const & x, int const order){
    return pow(log(x), order);
}

double naive_log_power_vec(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_log_power_order__(x, i);
    }
    return val;
}

double naive_log_power_iter(double const & x, Iter begin, Iter end) {
    double val = 0;
    int index = 0;
    for (auto it = begin; it != end; ++it, ++index) {
        val += *it * eval_log_power_order__(x, index);
    }
    return val;
}

double horner_log_power_custom_vec(double const & x, std::vector<double> const & coeffs){
    double f_x = log(x);
    double val = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i){
        val = val * f_x + coeffs[i];
    }
    return val;
}

double horner_log_power_custom_iter(double const & x, Iter begin, Iter end) {
    double f_x = std::log(x);
    double val = 0;
    for (auto it = end; it != begin; ) {
        --it;
        val = val * f_x + *it;
    }
    return val;
}

double horner_log_power_general_vec(double const & x, std::vector<double> const & coeffs){
    return horner(log(x), coeffs);
}

double horner_log_power_general_iter(double const & x, Iter begin, Iter end) {
    return horner(std::log(x), begin, end);
}

double clenshaw_log_power_custom_vec(double const & x, std::vector<double> const & coeffs) {
    double bk1 = 0;
    double bk = 0;
    double f_x = log(x);
    for (double k = coeffs.size(); k > 0; --k){
        bk = coeffs[k] + f_x*bk1;
        bk1 = bk;
    }
    return coeffs[0] + f_x*bk1;
}

double clenshaw_log_power_custom_iter(double const & x, Iter begin, Iter end) {
    double bk1 = 0;
    double bk = 0;
    double f_x = std::log(x);
    int size = std::distance(begin, end);
    for (int k = size - 1; k > 0; --k) {
        bk = *(begin + k) + f_x * bk1;
        bk1 = bk;
    }
    return *begin + f_x * bk1;
}

double clenshaw_log_power_general_vec(double const & x, std::vector<double> const & coeffs){
    return clenshaw(x, coeffs, log_power_alpha_recurrence__, log_power_beta_recurrence__, eval_log_power_order__);
}

double clenshaw_log_power_general_iter(double const & x, Iter begin, Iter end) {
    return clenshaw(x, begin, end, log_power_alpha_recurrence__, log_power_beta_recurrence__, eval_log_power_order__);
}