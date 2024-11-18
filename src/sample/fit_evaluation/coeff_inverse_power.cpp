#include <math.h>
#include <vector>

#include "coeff_inverse_power.hpp"

std::vector<double> eval_inverse_power_orders(double const &x, int const &n)
{
    std::vector<double> f(n + 1);
    f[0] = 1;
    double f1_x = 1.0 / x;
    if (n > 0) {f[1] = f1_x;}
    for (int i = 2; i <= n; ++i){
        f[i] = f1_x * f[i-1];
    }
    return f;
}
