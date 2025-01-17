#ifndef MAVOR_CLENSHAW_H
#define MAVOR_CLENSHAW_H

#include <vector>
#include <functional>
#include <iterator> 

/// @brief Evaluates a polynomial or series using the Clenshaw algorithm.
/// @param x The input value for the series evaluation.
/// @param coeffs The coefficients of the series.
/// @param alpha_rec Function to calculate the alpha recurrence coefficient. Takes `x` and an integer index `k` as arguments.
/// @param beta_rec Function to calculate the beta recurrence coefficient. Takes `x` and an integer index `k` as arguments.
/// @param phi Function representing the base series terms. Takes `x` and an integer index `k` as arguments.
/// @return The evaluated value of the series at `x`.
double clenshaw(double const & x, 
                std::vector<double> const & coeffs, 
                const std::function<double(double, int)>& alpha_rec, 
                const std::function<double(double, int)>& beta_rec, 
                const std::function<double(double, int)>& phi);

/// @brief Type alias for a constant iterator over a vector of doubles.
typedef std::vector<double>::const_iterator Iter;

/// @brief Evaluates a polynomial or series using the Clenshaw algorithm with iterators.
/// @param x The input value for the series evaluation.
/// @param begin Iterator pointing to the beginning of the coefficients range.
/// @param end Iterator pointing to the end of the coefficients range.
/// @param alpha_rec Function to calculate the alpha recurrence coefficient. Takes `x` and an integer index `k` as arguments.
/// @param beta_rec Function to calculate the beta recurrence coefficient. Takes `x` and an integer index `k` as arguments.
/// @param phi Function representing the base series terms. Takes `x` and an integer index `k` as arguments.
/// @return The evaluated value of the series at `x`.
double clenshaw(double const & x, 
                Iter begin, 
                Iter end, 
                const std::function<double(double, int)>& alpha_rec, 
                const std::function<double(double, int)>& beta_rec, 
                const std::function<double(double, int)>& phi);

#endif
