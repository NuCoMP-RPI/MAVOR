#ifndef MAVOR_LINEARIZE_H
#define MAVOR_LINEARIZE_H

#include <vector>
#include <functional>

/// @brief Linearizes a set of points by recursively adding intermediate points.
/// This function iteratively divides intervals between points and evaluates the 
/// new y-values using the provided function, adding new points where necessary.
/// 
/// @param x_points The x-values of the points to linearize.
/// @param y_points The y-values of the points to linearize.
/// @param get_new_y A function that computes the y-value for a given x-value.
/// @param absolute_tolerance The absolute tolerance for stopping refinement (default: 0.1).
/// @param relative_tolerance The relative tolerance for stopping refinement (default: 0.001).
/// 
/// This function will modify `x_points` and `y_points` by adding new points 
/// between the existing ones to improve the resolution based on the difference 
/// between the interpolated and actual y-values.
void linearize(std::vector<double>& x_points, std::vector<double>& y_points, std::function<double(double)> get_new_y, const double absolute_tolerance = 0.1, const double relative_tolerance = 0.001);

#endif