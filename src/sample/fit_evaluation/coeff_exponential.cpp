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

double naive_exponential(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_exponential_order__(x, i);
    }
    return val;
}

double horner_exponential_custom(double const & x, std::vector<double> const & coeffs){
    double exp_x = exp(x);
    double val = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i){
        val = val * exp_x + coeffs[i];
    }
    return val;
}

double horner_exponential_general(double const & x, std::vector<double> const & coeffs){
    return horner(exp(x), coeffs);
}

double clenshaw_exponential_custom(double const & x, std::vector<double> const & coeffs) {
    double bk1 = 0;
    double bk = 0;
    double exp_x = exp(x);
    for (double k = coeffs.size(); k > 0; --k){
        bk = coeffs[k] + exp_x*bk1;
        bk1 = bk;
    }
    return coeffs[0] + exp_x*bk1;
}

double clenshaw_exponential_general(double const & x, std::vector<double> const & coeffs){
    return clenshaw(x, coeffs, exponential_alpha_recurrence__, exponential_beta_recurrence__, eval_exponential_order__);
}