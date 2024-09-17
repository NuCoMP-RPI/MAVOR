#ifndef MAVOR_SAMPLE_EVAL_LEGENDRE_H
#define MAVOR_SAMPLE_EVAL_LEGENDRE_H

#include<vector>

double naive_legendre_vec(double const & x, std::vector<double> const & coeffs);
double direct_recurrence_legendre_custom_vec(double const & x, std::vector<double> const & coeffs);
double direct_recurrence_legendre_general_vec(double const & x, std::vector<double> const & coeffs);
double clenshaw_legendre_custom_vec(double const & x, std::vector<double> const & coeffs);
double clenshaw_legendre_general_vec(double const & x, std::vector<double> const & coeffs);

typedef std::vector<double>::const_iterator Iter;

double naive_legendre_iter(double const & x, Iter begin, Iter end);
double direct_recurrence_legendre_custom_iter(double const & x, Iter begin, Iter end);
double direct_recurrence_legendre_general_iter(double const & x, Iter begin, Iter end);
double clenshaw_legendre_custom_iter(double const & x, Iter begin, Iter end);
double clenshaw_legendre_general_iter(double const & x, Iter begin, Iter end);

#endif