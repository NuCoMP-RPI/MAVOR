#include <math.h>
#include <vector>

#include "coeff_sine.hpp"

#include "constants.hpp"

std::vector<double> eval_sine_orders(double const &x, int const &n)
{
    std::vector<double> f(n+1);
    double two_pi_x = 2.0*PI*x;
    f[0] = 1.0;
    for (int i = 1; i <= n; ++i){
        f[i] = sin(i*two_pi_x);
    }
    return f;
}
