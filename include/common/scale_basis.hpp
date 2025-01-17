#ifndef MAVOR_SCALE_BASIS_H
#define MAVOR_SCALE_BASIS_H

#include <vector>

/// @brief Scales a value into a new domain based off the span of the old domain and the new domain
/// @param x Value to scale
/// @param old_min Minimum of the current domain
/// @param old_max Maximum of the current domain
/// @param new_min Minimum of the new domain
/// @param new_max Maximum of the new domain
/// @return Scaled value in the new domain
double scale_value(double const & x, double const & old_min, double const & old_max, double const & new_min = -1, double const & new_max = 1);

/// @brief Scales a vector of doubles into a new domain based off the span of the vector and the new domain.
/// Takes the extrema of the vector to be the extrema of the current domain
/// @param x Vector of values to scale
/// @param new_min Minimum of the new domain
/// @param new_max Maximum of the new domain
/// @return Scaled vector in the new domain
std::vector<double> scale_array(std::vector<double> const & x, double const & new_min = -1, double const & new_max = 1);

#endif