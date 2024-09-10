#include <math.h>
#include <vector>

#include "horner.hpp"
#include "clenshaw.hpp"

#include "coeff_inverse_exponential.hpp"

double inverse_exponential_alpha_recurrence__(double const & x, int const & k){
    return exp(-x);
}

double inverse_exponential_beta_recurrence__(double const & x, int const & k){
    return 0;
}

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

double horner_inverse_exponential_custom(double const & x, std::vector<double> const & coeffs){
    double exp_x = exp(-x);
    double val = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i){
        val = val * exp_x + coeffs[i];
    }
    return val;
}

double horner_inverse_exponential_general(double const & x, std::vector<double> const & coeffs){
    return horner(exp(-x), coeffs);
}

double clenshaw_inverse_exponential_custom(double const & x, std::vector<double> const & coeffs) {
    double bk1 = 0;
    double bk = 0;
    double exp_x = exp(-x);
    for (double k = coeffs.size(); k > 0; --k){
        bk = coeffs[k] + exp_x*bk1;
        bk1 = bk;
    }
    return coeffs[0] + exp_x*bk1;
}

double clenshaw_inverse_exponential_general(double const & x, std::vector<double> const & coeffs){
    return clenshaw(x, coeffs, inverse_exponential_alpha_recurrence__, inverse_exponential_beta_recurrence__, eval_inverse_exponential_order__);
}