#include <math.h>
#include <vector>

#include "horner.hpp"
#include "clenshaw.hpp"

#include "coeff_inverse_log_power.hpp"

double inverse_log_power_alpha_recurrence__(double const & x, int const & k){
    return 1.0/log(x);
}

double inverse_log_power_beta_recurrence__(double const & x, int const & k){
    return 0;
}

double eval_inverse_log_power_order__(double const & x, int const order){
    return pow(log(x), -order);
}

double naive_inverse_log_power(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_inverse_log_power_order__(x, i);
    }
    return val;
}

double horner_inverse_log_power_custom(double const & x, std::vector<double> const & coeffs){
    double f_x = 1.0/log(x);
    double val = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i){
        val = val * f_x + coeffs[i];
    }
    return val;
}

double horner_inverse_log_power_general(double const & x, std::vector<double> const & coeffs){
    return horner(1.0/log(x), coeffs);
}

double clenshaw_inverse_log_power_custom(double const & x, std::vector<double> const & coeffs) {
    double bk1 = 0;
    double bk = 0;
    double f_x = 1.0/log(x);
    for (double k = coeffs.size(); k > 0; --k){
        bk = coeffs[k] + f_x*bk1;
        bk1 = bk;
    }
    return coeffs[0] + f_x*bk1;
}

double clenshaw_inverse_log_power_general(double const & x, std::vector<double> const & coeffs){
    return clenshaw(x, coeffs, inverse_log_power_alpha_recurrence__, inverse_log_power_beta_recurrence__, eval_inverse_log_power_order__);
}