#include <math.h>
#include <vector>

#include "coeff_legendre.hpp"

double eval_legendre_order__(double const & x, int const order){
    switch (order){
        case 0:
            return 1.0;
        case 1:
            return x;
        case 2:
            return (3.0*pow(x, 2) - 1.0)/2.0;
        case 3:
            return x*(5.0*pow(x, 2) - 3.0)/2.0;
        case 4:
            return (35.0*pow(x, 4) - 30.0*pow(x, 2) + 3.0)/8.0;
        case 5:
            return x*(63.0*pow(x, 4) - 70.0*pow(x, 2) + 15.0)/8.0;
        case 6:
            return (231.0*pow(x, 6) - 315.0*pow(x, 4) + 105.0*pow(x, 2) - 5.0)/16.0;
        case 7:
            return x*(429.0*pow(x, 6) - 693.0*pow(x, 4) + 315.0*pow(x, 2) - 35.0)/16.0;
        case 8:
            return (6435.0*pow(x, 8) - 12012.0*pow(x, 6) + 6930.0*pow(x, 4) - 1260.0*pow(x, 2) + 35.0)/128.0;
        case 9:
            return x*(12155.0*pow(x, 8) - 25740.0*pow(x, 6) + 18018.0*pow(x, 4) - 4620.0*pow(x, 2) + 315.0)/128.0;
        case 10:
            return (46189.0*pow(x, 10) - 109395.0*pow(x, 8) + 45045.0*pow(x, 6) - 15015.0*pow(x, 4) + 3465.0*pow(x, 2) - 63.0)/256.0;
        case 11:
            return x*(88179.0*pow(x, 10) - 230945.0*pow(x, 8) + 218790.0*pow(x, 6) - 90090.0*pow(x, 4) + 15015.0*pow(x, 2) - 693.0)/256.0;
        case 12:
            return (676039.0*pow(x, 12) - 1939938.0*pow(x, 10) + 2078505.0*pow(x, 8) - 1021020.0*pow(x, 6) + 225225.0*pow(x, 4) - 18018.0*pow(x, 2) + 231.0)/1024.0;
        case 13:
            return x*(1300075.0*pow(x, 12) - 4056234.0*pow(x, 10) + 4849845.0*pow(x, 8) - 2771340.0*pow(x, 6) + 765765.0*pow(x, 4) - 90090.0*pow(x, 2) + 3003.0)/1024.0;
        case 14:
            return (5014575.0*pow(x, 14) - 16900975.0*pow(x, 12) + 22309287.0*pow(x, 10) - 14549535.0*pow(x, 8) + 4849845.0*pow(x, 6) - 765765.0*pow(x, 4) + 45045.0*pow(x, 2) - 429.0)/2048.0;
        default:
            return ((2*order - 1)*x*eval_legendre_order__(x, order-1) - (order-1)*eval_legendre_order__(x, order-2))/order;
    }
}

double naive_legendre(double const & x, std::vector<double> const& coeffs){
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*eval_legendre_order__(x, i);
    }
    return val;
}