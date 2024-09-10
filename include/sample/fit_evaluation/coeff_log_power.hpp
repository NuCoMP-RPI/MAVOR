#ifndef MAVOR_SAMPLE_EVAL_LOG_POWER_H
#define MAVOR_SAMPLE_EVAL_LOG_POWER_H

#include<vector>

double naive_log_power(double const & x, std::vector<double> const& coeffs);
double horner_log_power_custom(double const & x, std::vector<double> const & coeffs);
double horner_log_power_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_log_power_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_log_power_general(double const & x, std::vector<double> const & coeffs);

#endif