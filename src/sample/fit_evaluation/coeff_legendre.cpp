#include <math.h>
#include <vector>

#include "clenshaw.hpp"

#include "coeff_legendre.hpp"

double legendre_alpha_recurrence__(double const & x, int const & k){
    return  ((2.0*k + 1.0)/(k + 1.0))*x;
}

double legendre_beta_recurrence__(double const & x, int const & k){
    return - k/(k + 1.0);
}

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

double direct_recurrence_legendre_custom(double const & x, std::vector<double> const & coeffs){
    size_t n = coeffs.size();
    if (n == 0) {
        return 0.0;
    }
    double P_prev = 1.0;
    double result = coeffs[0] * P_prev;
    if (n == 1) {
        return result;
    }
    double P_curr = x;
    result += coeffs[1] * P_curr;
    for (size_t i = 2; i < n; ++i) {
        double P_next = legendre_alpha_recurrence__(x,i-1) * P_curr + legendre_beta_recurrence__(x,i-1) * P_prev;
        result += coeffs[i] * P_next;
        P_prev = P_curr;
        P_curr = P_next;
    }
    return result;
}

std::vector<double> eval_legendre_direct_recurrence__(double x, int n) {
    std::vector<double> T(n + 1);
    T[0] = 1;
    if (n > 0) {T[1] = x;}
    for (int i = 2; i <= n; ++i){
        T[i] = legendre_alpha_recurrence__(x,i-1)*T[i-1] + legendre_beta_recurrence__(x,i-1)*T[i-2];
    }
    return T;
}

double direct_recurrence_legendre_general(double const & x, std::vector<double> const & coeffs){
    std::vector<double> leg_points = eval_legendre_direct_recurrence__(x, coeffs.size());
    double val = 0;
    for (int i = 0; i < coeffs.size(); ++i){
        val += coeffs[i]*leg_points[i];
    }
    return val;
}

double clenshaw_legendre_custom(double const & x, std::vector<double> const & coeffs) {
    double bk2 = 0;
    double bk1 = 0;
    double bk = 0;
    for (int k = coeffs.size() - 1; k > 0; --k) {
        bk = coeffs[k] + legendre_alpha_recurrence__(x, k) * bk1 + legendre_beta_recurrence__(x, k + 1) * bk2;
        bk2 = bk1;
        bk1 = bk;
    }
    return coeffs[0] + x*bk1 - 0.5*bk2;
}

double clenshaw_legendre_general(double const & x, std::vector<double> const & coeffs){
    return clenshaw(x, coeffs, legendre_alpha_recurrence__, legendre_beta_recurrence__, eval_legendre_order__);
}