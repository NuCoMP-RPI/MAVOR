#include <vector>
#include <iterator>

#include "horner.hpp"

double horner(double const & f_x, std::vector<double> const & coeffs) {
    double val = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        val = val * f_x + coeffs[i];
    }
    return val;
}

double horner(double const & f_x, Iter begin, Iter end) {
    double val = 0;
    for (auto it = end; it != begin; ) {
        --it;
        val = val * f_x + *it;
    }
    return val;
}