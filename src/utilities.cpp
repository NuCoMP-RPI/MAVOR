#include <vector>
#include <math.h>
#include <iostream>

#include "integration.hpp"
#include "interpolation.hpp"

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

std::vector<double> sigmoid_space(double const & low, double const & high, int const & num, double const & extent = 5){
    if (num<2){
        throw std::domain_error("'num' must be greater than 1.");        
    }
    else if (num==2)
    {
        return std::vector<double> {low, high};
    }
    else
    {
        std::vector<double> xs = linspace(-extent, extent, num);
        std::vector<double> ys;
        ys.reserve(xs.size());
        for (auto x:xs){
            ys.push_back((1/(1 + std::exp(-x)))*(high-low) + low);
        }
        ys.front() = low;
        ys.back() = high;
        return ys;
    }
}

std::vector<double> pdf_to_cdf(std::vector<double> const & x, std::vector<double> const & y, int const & integration_scheme){
    std::vector<double> cdf;
    cdf.resize(x.size());
    cdf[0] = 0;
    for (int i=1; i<x.size(); i++){
        cdf[i] = cdf[i-1] + ENDF_integrate(x[i-1], x[i], y[i-1], y[i], integration_scheme);
    }
    double factor = 1/cdf.back();
    for (int i=1; i<cdf.size(); i++){
        cdf[i] *= factor;
    }
    return cdf;
}

std::vector<double> fit_cdf(std::vector<double> const & x, std::vector<double> const & old_y, std::vector<double> const & new_y, int const & interpolation_scheme){
    std::vector<double> new_x;
    new_x.resize(new_y.size());
    for (int i=0; i<new_y.size(); i++){
        int insert = std::lower_bound(old_y.begin()+1, old_y.end(), new_y[i]) - old_y.begin();
        new_x[i] = ENDF_interp(old_y[insert-1], old_y[insert], x[insert-1], x[insert], new_y[i], interpolation_scheme);
    }
    return new_x;
}