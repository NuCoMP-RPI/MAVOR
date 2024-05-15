#include <vector>

double scale_value(double const & x, double const & old_min, double const & old_max, double const & new_min, double const & new_max){
    return ((x - old_min)/(old_max - old_min))*(new_max - new_min) + new_min;
}

std::vector<double> scale_array(std::vector<double> const & x, double const & new_min, double const & new_max){
    std::vector<double> result(x);
    for (int i = 0; i<x.size(); ++i){
        result[i] = scale_value(x[i], x.front(), x.back(), new_min, new_max);
    }
    return result;
}