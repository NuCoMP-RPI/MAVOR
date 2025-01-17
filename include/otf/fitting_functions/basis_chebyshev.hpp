#ifndef MAVOR_CHEBYSHEV_H
#define MAVOR_CHEBYSHEV_H

/// @brief Evaluates the Chebyshev polynomial of the first kind at a given order and input value.
/// @param x The input value at which the Chebyshev polynomial is evaluated.
/// @param order The order of the Chebyshev polynomial. Must be a non-negative integer.
/// @return The value of the Chebyshev polynomial of the specified order evaluated at x.
/// @throws std::range_error if the order is negative.
double eval_chebyshev_order(double const & x, int const order);

#endif