#include <math.h>
#include <vector>

#include "chebyshev.hpp"

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

double naive_chebyshev(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_chebyshev_order__(x, i);
    }
    return val;
}

