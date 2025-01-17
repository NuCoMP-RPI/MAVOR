#ifndef MAVOR_UTILITIES_H
#define MAVOR_UTILITIES_H

#include <vector>

/// @brief Generates a linearly spaced vector of values.
///
/// This function generates a vector of values starting at `start` and ending at `stop`,
/// with a specified number of points (`num`). The values are spaced evenly between
/// `start` and `stop`, inclusive.
///
/// @param start The starting value of the range.
/// @param stop The ending value of the range.
/// @param num_points The number of points to generate.
/// @return A vector of doubles containing the linearly spaced values.
std::vector<double> linspace(double const& start, double const& stop, int const& num_points);

/// @brief Generates a linearly spaced vector of values.
///
/// This function generates a vector of values starting at `start` and ending at `stop`,
/// with a specified number of points (`num`). The values are spaced logrithmically between
/// `start` and `stop`, inclusive.
///
/// @param start The starting value of the range.
/// @param stop The ending value of the range.
/// @param num_points The number of points to generate.
/// @return A vector of doubles containing the logrithmically spaced values.
std::vector<double> logspace(double const& start, double const& stop, int const& num_points);

/// @brief Generates a sigmoidally spaced vector of values. (Denser at the extrema)
///
/// This function generates a vector of values starting at `start` and ending at `stop`,
/// with a specified number of points (`num`). The values are spaced sigmoidally between
/// `start` and `stop`, inclusive.
///
/// @param low The starting value of the range.
/// @param high The ending value of the range.
/// @param num The number of points to generate.
/// @param extent The relative density at the extrema.  Higher extent means more dense.
/// @return A vector of doubles containing the sigmoidally spaced values.
std::vector<double> sigmoid_space(double const & low, double const & high, int const & num, double const & extent = 5);

/// @brief Converts a PDF into a CDF using the given ENDF integration scheme
/// @param x Vector of doubles with the PDF evaluation points
/// @param y Vector of doubles with the PDF values
/// @param integration_scheme ENDF integration scheme
/// @return Vector of the CDF values
std::vector<double> pdf_to_cdf(std::vector<double> const & x, std::vector<double> const & y, int const & integration_scheme = 2);

/// @brief Takes a set of CDF points and values and finds the new points that would correspond to the passed new CDF values.
/// This function , essentailly, allows the the points to value dependence to be reverse so that CDF values map to points.
/// @param x Vector of doubles with the CDF evaluation points
/// @param old_y Vector of doubles with the CDF values
/// @param new_y Vector of doubles with the desired CDF values 
/// @param interpolation_scheme ENDF interpolation scheme to calculate the new CDF points
/// @return Vector of doubles containing the new CDF points that correspond to the passed desired CDF values
std::vector<double> fit_cdf(std::vector<double> const & x, std::vector<double> const & old_y, std::vector<double> const & new_y, int const & interpolation_scheme = 2);

#endif