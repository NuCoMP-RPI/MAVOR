#include <iostream>
#include <math.h>

double ENDF_interp_scheme_1(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1;
}

double ENDF_interp_scheme_2(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1 + (y2 - y1) * ((x - x1) / (x2 - x1));
}

double ENDF_interp_scheme_3(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1 + (y2 - y1)*(log(x/x1)/log(x2/x1));
}

double ENDF_interp_scheme_4(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1*exp(log(y2/y1)*((x - x1)/(x2 - x1)));
}

double ENDF_interp_scheme_5(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1*exp(log(x/x1)*(log(y2/y1)/log(x2/x1)));
}

double ENDF_interp(double const & x1, double const & x2, double const & y1, double const & y2, double const & x, int const scheme = 2){
    switch (scheme)
    {
    case 1:
        return ENDF_interp_scheme_1(x1, x2, y1, y2, x);
    case 2:
        return ENDF_interp_scheme_2(x1, x2, y1, y2, x);        
    case 3:
        return ENDF_interp_scheme_3(x1, x2, y1, y2, x);
    case 4:
        return ENDF_interp_scheme_4(x1, x2, y1, y2, x);
    case 5:
        return ENDF_interp_scheme_5(x1, x2, y1, y2, x);
    default:
        throw std::invalid_argument("Scheme type was not recognized.");
    }
}

double bi_interp(double const & x1, double const & x2, double const & y1, double const & y2, 
                 double const & f11, double const & f12, double const & f21, double const & f22, 
                 double const & x, double const & y, 
                 int const x_scheme = 2, int const y_scheme = 2){
    double fxy1 = ENDF_interp(x1, x2, f11, f21, x, x_scheme);
    double fxy2 = ENDF_interp(x1, x2, f12, f22, x, x_scheme);
    return ENDF_interp(y1, y2, fxy1, fxy2, y, y_scheme);
}


