#ifndef MAVOR_INTEGRATION_H
#define MAVOR_INTEGRATION_H

#include <vector>

/// @brief Performs integration using Scheme 1: Constant y1 over the interval [x1, x2].
/// @param x1 Start of the interval.
/// @param x2 End of the interval.
/// @param y1 Function value at x1.
/// @param y2 Function value at x2 (not used in this scheme).
/// @return The integral value.
double ENDF_integral_scheme_1(double const& x1, double const& x2, double const& y1, double const& y2);

/// @brief Performs integration using Scheme 2: Linear interpolation between y1 and y2.
/// @param x1 Start of the interval.
/// @param x2 End of the interval.
/// @param y1 Function value at x1.
/// @param y2 Function value at x2.
/// @return The integral value.
double ENDF_integral_scheme_2(double const& x1, double const& x2, double const& y1, double const& y2);

/// @brief Performs integration using Scheme 3: Logarithmic interpolation between y1 and y2.
/// @param x1 Start of the interval.
/// @param x2 End of the interval.
/// @param y1 Function value at x1.
/// @param y2 Function value at x2.
/// @return The integral value.
double ENDF_integral_scheme_3(double const& x1, double const& x2, double const& y1, double const& y2);

/// @brief Performs integration using Scheme 4: Log-log interpolation between y1 and y2.
/// @param x1 Start of the interval.
/// @param x2 End of the interval.
/// @param y1 Function value at x1.
/// @param y2 Function value at x2.
/// @return The integral value.
double ENDF_integral_scheme_4(double const& x1, double const& x2, double const& y1, double const& y2);

/// @brief Performs integration using Scheme 5: Power-law interpolation between y1 and y2.
/// @param x1 Start of the interval.
/// @param x2 End of the interval.
/// @param y1 Function value at x1.
/// @param y2 Function value at x2.
/// @return The integral value.
double ENDF_integral_scheme_5(double const& x1, double const& x2, double const& y1, double const& y2);

/// @brief Integrates a single interval using a specified scheme.
/// @param x1 Start of the interval.
/// @param x2 End of the interval.
/// @param y1 Function value at x1.
/// @param y2 Function value at x2.
/// @param scheme The scheme to use (1-5).
/// @return The integral value.
double ENDF_integrate(double const& x1, double const& x2, double const& y1, double const& y2, int const scheme);

/// @brief Integrates over a vector of intervals using a specified scheme.
/// @param x_a Vector of x values.
/// @param y_a Vector of y values corresponding to x_a.
/// @param scheme The scheme to use (1-5).
/// @return The integral value.
double ENDF_integrate_vector(std::vector<double> const& x_a, std::vector<double> const& y_a, int const scheme);


#endif