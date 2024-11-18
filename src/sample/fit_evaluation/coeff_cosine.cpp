#include <math.h>
#include <vector>
#include <iterator>

#include "coeff_cosine.hpp"

#include "constants.hpp"

std::vector<double> eval_cosine_orders(double const &x, int const &n)
{
    std::vector<double> f(n+1);
    double two_pi_x = 2.0*PI*x;
    for (int i = 0; i <= n; ++i){
        f[i] = cos(i*two_pi_x);
    }
    return f;
}
