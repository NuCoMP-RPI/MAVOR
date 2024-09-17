#ifndef MAVOR_SAMPLE_EVAL_CHEBYSHEV_H
#define MAVOR_SAMPLE_EVAL_CHEBYSHEV_H

#include<vector>

double naive_chebyshev_vec(double const & x, std::vector<double> const & coeffs);
double direct_recurrence_chebyshev_custom_vec(double const & x, std::vector<double> const & coeffs);
double direct_recurrence_chebyshev_general_vec(double const & x, std::vector<double> const & coeffs);
double clenshaw_chebyshev_custom_vec(double const & x, std::vector<double> const & coeffs);
double clenshaw_chebyshev_general_vec(double const & x, std::vector<double> const & coeffs);

typedef std::vector<double>::const_iterator Iter;

double naive_chebyshev_iter(double const & x, Iter begin, Iter end);
double direct_recurrence_chebyshev_custom_iter(double const & x, Iter begin, Iter end);
double direct_recurrence_chebyshev_general_iter(double const & x, Iter begin, Iter end);
double clenshaw_chebyshev_custom_iter(double const & x, Iter begin, Iter end);
double clenshaw_chebyshev_general_iter(double const & x, Iter begin, Iter end);

#endif