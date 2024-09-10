#ifndef MAVOR_SAMPLE_EVAL_INVERSE_EXPONENTIAL_H
#define MAVOR_SAMPLE_EVAL_INVERSE_EXPONENTIAL_H

#include<vector>

double naive_inverse_exponential(double const & x, std::vector<double> const& coeffs);
double horner_inverse_exponential_custom(double const & x, std::vector<double> const & coeffs);
double horner_inverse_exponential_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_exponential_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_exponential_general(double const & x, std::vector<double> const & coeffs);

#endif