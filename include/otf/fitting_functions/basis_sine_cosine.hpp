#ifndef MAVOR_SINE_COSINE_H
#define MAVOR_SINE_COSINE_H

/// @brief Evaluates the sine-cosine basis function for a given order and input value.
/// @param x The input value.
/// @param order The order of the sine-cosine basis function. 
/// @return The value of the sine-cosine basis function of the specified order at x.
///         Returns 1 if order is 0, sine for even orders, and cosine for odd orders.
double eval_sine_cosine_order(double const & x, int const order);

#endif