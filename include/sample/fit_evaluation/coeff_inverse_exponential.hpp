#ifndef MAVOR_SAMPLE_EVAL_INVERSE_EXPONENTIAL_H
#define MAVOR_SAMPLE_EVAL_INVERSE_EXPONENTIAL_H

#include<vector>

double naive_inverse_exponential_vec(double const & x, std::vector<double> const & coeffs);
double horner_inverse_exponential_custom_vec(double const & x, std::vector<double> const & coeffs);
double horner_inverse_exponential_general_vec(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_exponential_custom_vec(double const & x, std::vector<double> const & coeffs);
double clenshaw_inverse_exponential_general_vec(double const & x, std::vector<double> const & coeffs);

typedef std::vector<double>::const_iterator Iter;

double naive_inverse_exponential_iter(double const & x, Iter begin, Iter end);
double horner_inverse_exponential_custom_iter(double const & x, Iter begin, Iter end);
double horner_inverse_exponential_general_iter(double const & x, Iter begin, Iter end);
double clenshaw_inverse_exponential_custom_iter(double const & x, Iter begin, Iter end);
double clenshaw_inverse_exponential_general_iter(double const & x, Iter begin, Iter end);

#endif