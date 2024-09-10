#include <vector>

double horner(double const & f_x, std::vector<double> const & coeffs) {
    double val = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        val = val * f_x + coeffs[i];
    }
    return val;
}