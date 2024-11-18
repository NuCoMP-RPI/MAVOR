#ifndef MAVOR_SAMPLE_EVAL_SQRT_POWER_H
#define MAVOR_SAMPLE_EVAL_SQRT_POWER_H

#include<vector>

/**
 * @brief Evaluates sqrt power functions at the given x up to order n and returns the results in a vector
 * @param x Value at which to evaluate the functions
 * @param n Max order to evaluate the functions
 * @return std::vector<double>(n+1) of the evaluated sqrt power functions in ascending order
 */
std::vector<double> eval_sqrt_power_orders(double const &x, int const &n);

#endif