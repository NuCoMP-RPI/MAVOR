#ifndef MAVOR_HORNER_H
#define MAVOR_HORNER_H

#include <vector>

/// @brief Evaluates a polynomial using Horner's method with coefficients stored in a vector.
/// @param f_x The input value for which the polynomial is evaluated.
/// @param coeffs The vector of coefficients, ordered from lowest to highest degree (i.e., coeff[0] corresponds to the constant term).
/// @return The evaluated value of the polynomial.
double horner(double const& f_x, std::vector<double> const& coeffs);

/// @brief Alias for a constant iterator over a vector of doubles.
typedef std::vector<double>::const_iterator Iter;

/// @brief Evaluates a polynomial using Horner's method with coefficients accessed via iterators.
/// @param f_x The input value for which the polynomial is evaluated.
/// @param begin Iterator pointing to the beginning of the coefficients.
/// @param end Iterator pointing to one past the last coefficient.
/// @return The evaluated value of the polynomial.
double horner(double const& f_x, Iter begin, Iter end);

#endif