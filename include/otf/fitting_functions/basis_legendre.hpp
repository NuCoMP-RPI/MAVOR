#ifndef MAVOR_LEGENDRE_H
#define MAVOR_LEGENDRE_H

/// @brief Evaluates the Legendre polynomial of the given order at the input value.
/// @param x The input value.
/// @param order The order of the Legendre polynomial. Must be a non-negative integer.
/// @return The value of the Legendre polynomial of the specified order at x.
/// @throws std::range_error if the order is negative.
double eval_legendre_order(double const & x, int const order);

#endif