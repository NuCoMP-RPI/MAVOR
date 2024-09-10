#ifndef MAVOR_SAMPLE_EVAL_POWER_H
#define MAVOR_SAMPLE_EVAL_POWER_H

#include<vector>

double naive_power(double const & x, std::vector<double> const& coeffs);
double horner_power_custom(double const & x, std::vector<double> const & coeffs);
double horner_power_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_power_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_power_general(double const & x, std::vector<double> const & coeffs);

#endif