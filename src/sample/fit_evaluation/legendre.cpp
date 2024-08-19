#include <math.h>
#include <vector>

#include "legendre.hpp"

double eval_legendre_order__(double const & x, int const order){
    switch (order){
        case 0:
            return 1;
        case 1:
            return x;
        case 2:
            return 3*pow(x, 2)/2 - 1/2;
        case 3:
            return x*(5*pow(x, 2) - 3)/2;
        case 4:
            return 35*pow(x, 4)/8 - 15*pow(x, 2)/4 + 3/8;
        case 5:
            return x*(63*pow(x, 4) - 70*pow(x, 2) + 15)/8;
        case 6:
            return 231*pow(x, 6)/16 - 315*pow(x, 4)/16 + 105*pow(x, 2)/16 - 5/16;
        case 7:
            return x*(429*pow(x, 6) - 693*pow(x, 4) + 315*pow(x, 2) - 35)/16;
        case 8:
            return 6435*pow(x, 8)/128 - 3003*pow(x, 6)/32 + 3465*pow(x, 4)/64 - 315*pow(x, 2)/32 + 35/128;
        case 9:
            return x*(12155*pow(x, 8) - 25740*pow(x, 6) + 18018*pow(x, 4) - 4620*pow(x, 2) + 315)/128;
        case 10:
            return 46189*pow(x, 10)/256 - 109395*pow(x, 8)/256 + 45045*pow(x, 6)/128 - 15015*pow(x, 4)/128 + 3465*pow(x, 2)/256 - 63/256;
        case 11:
            return x*(88179*pow(x, 10) - 230945*pow(x, 8) + 218790*pow(x, 6) - 90090*pow(x, 4) + 15015*pow(x, 2) - 693)/256;
        case 12:
            return 676039*pow(x, 12)/1024 - 969969*pow(x, 10)/512 + 2078505*pow(x, 8)/1024 - 255255*pow(x, 6)/256 + 225225*pow(x, 4)/1024 - 9009*pow(x, 2)/512 + 231/1024;
        case 13:
            return x*(1300075*pow(x, 12) - 4056234*pow(x, 10) + 4849845*pow(x, 8) - 2771340*pow(x, 6) + 765765*pow(x, 4) - 90090*pow(x, 2) + 3003)/1024;
        case 14:
            return 5014575*pow(x, 14)/2048 - 16900975*pow(x, 12)/2048 + 22309287*pow(x, 10)/2048 - 14549535*pow(x, 8)/2048 + 4849845*pow(x, 6)/2048 - 765765*pow(x, 4)/2048 + 45045*pow(x, 2)/2048 - 429/2048;
        default:
            return ((2*order - 1)*x*eval_legendre_order__(order-1, x) - (order-1)*eval_legendre_order__(order-2, x))/order;
    }
}

double naive_legendre(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_legendre_order__(x, i);
    }
    return val;
}