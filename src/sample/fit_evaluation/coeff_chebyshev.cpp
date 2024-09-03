#include <math.h>
#include <vector>
#include <functional>

#include "clenshaw.hpp"

#include "coeff_chebyshev.hpp"

double chebyshev_alpha_recurrence__(double const & x, int const & k){
    return 2*x;
}

double chebyshev_beta_recurrence__(double const & x, int const & k){
    return -1;
}

double eval_chebyshev_order__(double const & x, int const order){
    switch(order){
        case 0:
            return 1;
        case 1:
            return x;
        case 2:
            return 2*pow(x, 2) - 1;
        case 3:
            return x*(4*pow(x, 2) - 3);
        case 4:
            return 8*pow(x, 4) - 8*pow(x, 2) + 1;
        case 5:
            return x*(16*pow(x, 4) - 20*pow(x, 2) + 5);
        case 6:
            return 32*pow(x, 6) - 48*pow(x, 4) + 18*pow(x, 2) - 1;
        case 7:
            return x*(64*pow(x, 6) - 112*pow(x, 4) + 56*pow(x, 2) - 7);
        case 8:
            return 128*pow(x, 8) - 256*pow(x, 6) + 160*pow(x, 4) - 32*pow(x, 2) + 1;
        case 9:
            return x*(256*pow(x, 8) - 576*pow(x, 6) + 432*pow(x, 4) - 120*pow(x, 2) + 9);
        case 10:
            return 512*pow(x, 10) - 1280*pow(x, 8) + 1120*pow(x, 6) - 400*pow(x, 4) + 50*pow(x, 2) - 1;
        case 11:
            return x*(1024*pow(x, 10) - 2816*pow(x, 8) + 2816*pow(x, 6) - 1232*pow(x, 4) + 220*pow(x, 2) - 11);
        case 12:
            return 2048*pow(x, 12) - 6144*pow(x, 10) + 6912*pow(x, 8) - 3584*pow(x, 6) + 840*pow(x, 4) - 72*pow(x, 2) + 1;
        case 13:
            return x*(4096*pow(x, 12) - 13312*pow(x, 10) + 16640*pow(x, 8) - 9984*pow(x, 6) + 2912*pow(x, 4) - 364*pow(x, 2) + 13);
        case 14:
            return 8192*pow(x, 14) - 28672*pow(x, 12) + 39424*pow(x, 10) - 26880*pow(x, 8) + 9408*pow(x, 6) - 1568*pow(x, 4) + 98*pow(x, 2) - 1;
        default:
            return 2*x*eval_chebyshev_order__(order-1, x) - eval_chebyshev_order__(order-2, x);
    }
}

double naive_chebyshev(double const & x, std::vector<double> const & coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_chebyshev_order__(x, i);
    }
    return val;
}

std::vector<double> eval_chebyshev_direct_recurrence__(double x, int n) {
    std::vector<double> T(n + 1);
    T[0] = 1;
    if (n > 0) {T[1] = x;}
    for (int i = 2; i <= n; ++i){
        T[i] = 2 * x * T[i-1] - T[i-2];
    }
    return T;
}

double direct_recurrence_chebyshev(double const & x, std::vector<double> const & coeffs){
    std::vector<double> cheb_points = eval_chebyshev_direct_recurrence__(x, coeffs.size());
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*cheb_points[i];
    }
    return val;
}

double clenshaw_chebyshev_custom(double const & x, std::vector<double> const & coeffs) {
    double bk2 = 0;
    double bk1 = 0;
    double bk = 0;
    for (double k = coeffs.size(); k > 0; --k){
        bk = coeffs[k] + 2*x*bk1 - bk2;
        bk2 = bk1;
        bk1 = bk;
    }
    return coeffs[0] + x*bk1 - bk2;
}

double clenshaw_chebyshev_general(double const & x, std::vector<double> const & coeffs){
    return clenshaw(x, coeffs, chebyshev_alpha_recurrence__, chebyshev_beta_recurrence__, eval_chebyshev_order__);
}
