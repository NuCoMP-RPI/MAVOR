#ifndef MAVOR_INTERPOLATION_H
#define MAVOR_INTERPOLATION_H

#include <vector>

/// @brief Interpolation scheme 1: Returns the first y value (y1).
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1 The first y value.
/// @param y2 The second y value.
/// @param x The value to interpolate at.
/// @return The interpolated y value (y1).
double ENDF_interp_scheme_1(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);

/// @brief Interpolation scheme 2: Performs linear interpolation between (x1, y1) and (x2, y2).
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1 The first y value.
/// @param y2 The second y value.
/// @param x The value to interpolate at.
/// @return The interpolated y value.
double ENDF_interp_scheme_2(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);

/// @brief Interpolation scheme 3: Performs logarithmic interpolation between (x1, y1) and (x2, y2).
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1 The first y value.
/// @param y2 The second y value.
/// @param x The value to interpolate at.
/// @return The interpolated y value.
double ENDF_interp_scheme_3(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);

/// @brief Interpolation scheme 4: Performs exponential interpolation between (x1, y1) and (x2, y2).
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1 The first y value.
/// @param y2 The second y value.
/// @param x The value to interpolate at.
/// @return The interpolated y value.
double ENDF_interp_scheme_4(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);

/// @brief Interpolation scheme 5: Performs a more complex interpolation between (x1, y1) and (x2, y2).
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1 The first y value.
/// @param y2 The second y value.
/// @param x The value to interpolate at.
/// @return The interpolated y value.
double ENDF_interp_scheme_5(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);

/// @brief General interpolation function that selects the appropriate interpolation scheme.
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1 The first y value.
/// @param y2 The second y value.
/// @param x The value to interpolate at.
/// @param scheme The interpolation scheme to use (default is 2).
/// @return The interpolated y value.
double ENDF_interp(double const & x1, double const & x2, double const & y1, double const & y2, double const & x, int const scheme = 2);

/// @brief Vector-based interpolation that applies the specified interpolation scheme to each pair of y values.
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1_vec A vector of the first y values.
/// @param y2_vec A vector of the second y values.
/// @param x The value to interpolate at.
/// @param scheme The interpolation scheme to use (default is 2).
/// @return A vector of interpolated y values.
std::vector<double> ENDF_interp_vector(double const & x1, double const & x2, std::vector<double> const & y1_vec, std::vector<double> const & y2_vec, double const & x, int const scheme = 2);

/// @brief Bilinear interpolation for a grid of points.
/// Interpolation over the x values is conducted first, and then interpolation over the y values.
/// @param x1 The first x value.
/// @param x2 The second x value.
/// @param y1 The first y value.
/// @param y2 The second y value.
/// @param f11 The function value at (x1, y1).
/// @param f12 The function value at (x1, y2).
/// @param f21 The function value at (x2, y1).
/// @param f22 The function value at (x2, y2).
/// @param x The x value to interpolate at.
/// @param y The y value to interpolate at.
/// @param x_scheme The interpolation scheme for the x direction.
/// @param y_scheme The interpolation scheme for the y direction.
/// @return The interpolated value at (x, y).
double bi_interp(double const & x1, double const & x2, double const & y1, double const & y2, 
                 double const & f11, double const & f12, double const & f21, double const & f22, 
                 double const & x, double const & y, 
                 int const x_scheme = 2, int const y_scheme = 2);

/// @brief Finds the indices of the two points in an array that surround a given value.
/// @param array The array of x values.
/// @param val The value to find the surrounding points for.
/// @return A pair of indices: the lower and upper bounds of the surrounding points.
std::pair<size_t, size_t> findInterpolationIndexes(const std::vector<double>& array, double val);

/// @brief Finds the indices of the two points in a range that surround a given value.
/// @param begin The start iterator of the range.
/// @param end The end iterator of the range.
/// @param val The value to find the surrounding points for.
/// @return A pair of indices: the lower and upper bounds of the surrounding points.
std::pair<size_t, size_t> findInterpolationIndexes(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end, double val);

#endif