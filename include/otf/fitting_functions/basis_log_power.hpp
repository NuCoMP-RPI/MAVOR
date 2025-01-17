#ifndef MAVOR_LOG_POWER_H
#define MAVOR_LOG_POWER_H

/// @brief Evaluates the logarithmic power basis function for a given order and input value.
/// @param x The input value (must be greater than 0).
/// @param order The order of the logarithmic power basis function.
/// @return The value of the logarithmic power basis function of the specified order at x.
double eval_log_power_order(double const & x, int const order);

#endif