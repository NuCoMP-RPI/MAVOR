#ifndef MAVOR_SCALE_BASIS_H
#define MAVOR_SCALE_BASIS_H

#include <vector>

double scale_value(double const & x, double const & old_min, double const & old_max, double const & new_min = -1, double const & new_max = 1);
std::vector<double> scale_array(std::vector<double> const & x, double const & new_min = -1, double const & new_max = 1);

#endif