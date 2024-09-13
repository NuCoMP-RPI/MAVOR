#ifndef MAVOR_SAMPLE_EVAL_LEGENDRE_H
#define MAVOR_SAMPLE_EVAL_LEGENDRE_H

#include<vector>

double naive_legendre(double const & x, std::vector<double> const& coeffs);
double direct_recurrence_legendre_custom(double const & x, std::vector<double> const & coeffs);
double direct_recurrence_legendre_general(double const & x, std::vector<double> const & coeffs);
double clenshaw_legendre_custom(double const & x, std::vector<double> const & coeffs);
double clenshaw_legendre_general(double const & x, std::vector<double> const & coeffs);

#endif