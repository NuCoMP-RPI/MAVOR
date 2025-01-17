#ifndef MAVOR_SINE_H
#define MAVOR_SINE_H

/// @brief Evaluates the sine basis function for a given order and input value.
/// @param x The input value.
/// @param order The order of the sine basis function.
/// @return The value of the sine basis function of the specified order at x.
///         Returns 1 if order is 0.
double eval_sine_order(double const & x, int const order);

#endif