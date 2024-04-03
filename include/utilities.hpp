#ifndef MAVOR_UTILITIES_H
#define MAVOR_UTILITIES_H

#include <vector>

std::vector<double> linspace(double const& start, double const& stop, int const& num_points);
std::vector<double> logspace(double const& start, double const& stop, int const& num_points);

#endif