#ifndef MAVOR_SAMPLE_EVAL_CHEBYSHEV_H
#define MAVOR_SAMPLE_EVAL_CHEBYSHEV_H

#include<vector>

double naive_chebyshev(double const & x, std::vector<double> const & coeffs);
double direct_recurrence_chebyshev_custom(double const & x, std::vector<double> const & coeffs);
double direct_recurrence_chebyshev_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_chebyshev_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_chebyshev_general(double const & x, std::vector<double> const & coeffs);

#endif