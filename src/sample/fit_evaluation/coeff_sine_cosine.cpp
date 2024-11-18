#include <math.h>
#include <vector>

#include "coeff_sine_cosine.hpp"

#include "constants.hpp"

std::vector<double> eval_sine_cosine_orders(double const &x, int const &n)
{
    std::vector<double> f(n+1);
    double two_pi_x = 2*PI*x;
    f[0] = 1;
    for (int i = 1; i <= n; ++i){
        if (i%2 == 0) {f[i] = sin(int(i/2)*two_pi_x);}
        else {f[i] = cos(int(i/2)*two_pi_x);}
    }
    return f;
}
