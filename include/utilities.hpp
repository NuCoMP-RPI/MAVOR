#ifndef MAVOR_UTILITIES_H
#define MAVOR_UTILITIES_H

#include <vector>

std::vector<double> linspace(double const& start, double const& stop, int const& num_points);
std::vector<double> logspace(double const& start, double const& stop, int const& num_points);
std::vector<double> sigmoid_space(double const & low, double const & high, int const & num, double const & extent = 5);
std::vector<double> pdf_to_cdf(std::vector<double> const & x, std::vector<double> const & y, int const & integration_scheme = 2);
std::vector<double> fit_cdf(std::vector<double> const & x, std::vector<double> const & old_y, std::vector<double> const & new_y, int const & interpolation_scheme = 2);

#endif