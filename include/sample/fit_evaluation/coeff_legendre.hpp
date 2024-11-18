#ifndef MAVOR_SAMPLE_EVAL_LEGENDRE_H
#define MAVOR_SAMPLE_EVAL_LEGENDRE_H

#include<vector>

/**
 * @brief Evaluates the legendre polynomials at the given x up to order n and returns the results in a vector
 * @param x Value at which to evaluate the polynomials
 * @param n Max order to evaluate the polynomials
 * @return std::vector<double>(n+1) of the evaluated legendre polynomials in ascending order
 */
std::vector<double> eval_legendre_orders(double const &x, int const &n);

#endif