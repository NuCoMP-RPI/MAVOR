#ifndef MAVOR_SAMPLE_EVAL_EXPONENTIAL_H
#define MAVOR_SAMPLE_EVAL_EXPONENTIAL_H

#include<vector>

double naive_exponential(double const & x, std::vector<double> const& coeffs);
double horner_exponential_custom(double const & x, std::vector<double> const & coeffs);
double horner_exponential_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_exponential_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_exponential_general(double const & x, std::vector<double> const & coeffs);

#endif