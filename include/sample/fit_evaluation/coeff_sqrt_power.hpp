#ifndef MAVOR_SAMPLE_EVAL_SQRT_POWER_H
#define MAVOR_SAMPLE_EVAL_SQRT_POWER_H

#include<vector>

double naive_sqrt_power(double const & x, std::vector<double> const& coeffs);
double horner_sqrt_power_custom(double const & x, std::vector<double> const & coeffs);
double horner_sqrt_power_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_sqrt_power_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_sqrt_power_general(double const & x, std::vector<double> const & coeffs);

#endif