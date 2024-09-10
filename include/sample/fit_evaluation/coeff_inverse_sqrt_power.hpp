#ifndef INVERSE_SAMPLE_EVAL_SQRT_POWER_H
#define INVERSE_SAMPLE_EVAL_SQRT_POWER_H

#include<vector>

double naive_inverse_sqrt_power(double const & x, std::vector<double> const& coeffs);
double horner_inverse_sqrt_power_custom(double const & x, std::vector<double> const & coeffs);
double horner_inverse_sqrt_power_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_sqrt_power_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_sqrt_power_general(double const & x, std::vector<double> const & coeffs);

#endif