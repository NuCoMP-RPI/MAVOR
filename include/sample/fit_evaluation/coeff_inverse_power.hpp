#ifndef MAVOR_SAMPLE_EVAL_INVERSE_POWER_H
#define MAVOR_SAMPLE_EVAL_INVERSE_POWER_H

#include<vector>

double naive_inverse_power(double const & x, std::vector<double> const& coeffs);
double horner_inverse_power_custom(double const & x, std::vector<double> const & coeffs);
double horner_inverse_power_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_power_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_power_general(double const & x, std::vector<double> const & coeffs);

#endif