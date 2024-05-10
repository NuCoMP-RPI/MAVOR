#ifndef MAVOR_LINEARIZE_H
#define MAVOR_LINEARIZE_H

#include <vector>
#include <functional>

void linearize(std::vector<double>& x_points, std::vector<double>& y_points, std::function<double(double)> get_new_y);

#endif