#ifndef MAVOR_SAMPLE_EVAL_COSINE_H
#define MAVOR_SAMPLE_EVAL_COSINE_H

#include<vector>

/// @brief Evaluates cosine functions at the given x up to order n and returns the results in a vector
/// @param x Value at which to evaluate the functions
/// @param n Max order to evaluate the functions
/// @return std::vector<double>(n+1) of the evaluated cosine functions in ascending order
std::vector<double> eval_cosine_orders(double const &x, int const &n);

#endif