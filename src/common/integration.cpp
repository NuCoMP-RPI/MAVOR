#include <iostream>
#include <vector>
#include <math.h>

double ENDF_integral_scheme_1(double const & x1, double const & x2, double const & y1, double const & y2){
    return (x2 - x1) * y1;
}

double ENDF_integral_scheme_2(double const & x1, double const & x2, double const & y1, double const & y2){
    return (x2 - x1) * ((y1 + y2) / 2);
}

double ENDF_integral_scheme_3(double const & x1, double const & x2, double const & y1, double const & y2){
    double y2my1 = y2 - y1;
    double a = y2my1/log(x2/x1);
    return y1*(x2 - x1) + x2*(y2my1) + a*(x1 - x2);
}

double ENDF_integral_scheme_4(double const & x1, double const & x2, double const & y1, double const & y2){
    return (x2-x1)*(y2-y1)/log(y2/y1);
}

double ENDF_integral_scheme_5(double const & x1, double const & x2, double const & y1, double const & y2){
    double h = log(y2/y1)/log(x2/x1);
    return ((x1*y1)/(h + 1))*(pow((x2/x1), (h + 1)) - 1);
}

double ENDF_integrate(double const & x1, double const & x2, double const & y1, double const & y2, int const scheme){
    if (x1 == x2){
        return y1;
    }
    switch (scheme)
    {
    case 1:
        return ENDF_integral_scheme_1(x1, x2, y1, y2);
    case 2:
        return ENDF_integral_scheme_2(x1, x2, y1, y2);   
    case 3:
        return ENDF_integral_scheme_3(x1, x2, y1, y2);
    case 4:
        if (y1 == y2){
            return ENDF_integral_scheme_1(x1, x2, y1, y2);
        }
        else{
            return ENDF_integral_scheme_4(x1, x2, y1, y2);
        }
    case 5:
        return ENDF_integral_scheme_5(x1, x2, y1, y2);
 
    default:
        throw std::invalid_argument("Scheme type was not recognized.");
    }
}

double ENDF_integrate_vector(std::vector<double> const & x_a, std::vector<double> const & y_a, int const scheme){
    double val = 0;
    for (int i=0; i<y_a.size()-1; i++){
        val += ENDF_integrate(x_a[i], x_a[i+1], y_a[i], y_a[i+1], scheme);
    }
    return val;
}


