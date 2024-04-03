#include <vector>
#include <cmath>

std::vector<double> linspace(double const& start, double const& stop, int const& num_points){
    std::vector<double> result(num_points);
    double step = (stop - start) / (num_points - 1);
    for (int i = 0; i < num_points; ++i) {
        result[i] = start + i * step;
    }
    return result;
}

std::vector<double> logspace(double const& start, double const& stop, int const& num_points){
    std::vector<double> result(num_points);
    double log_start = std::log10(start);
    double log_stop = std::log10(stop);
    double step = (log_stop - log_start) / (num_points - 1);
    for (int i = 0; i < num_points; ++i) {
        double exponent = log_start + i * step;
        result[i] = std::pow(10, exponent);
    }
    return result;
}