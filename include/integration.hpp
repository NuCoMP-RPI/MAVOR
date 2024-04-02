#ifndef MAVOR_INTEGRATION_H
#define MAVOR_INTEGRATION_H

#include <vector>

double ENDF_integral_scheme_1(double const & x1, double const & x2, double const & y1, double const & y2);
double ENDF_integral_scheme_2(double const & x1, double const & x2, double const & y1, double const & y2);
double ENDF_integral_scheme_3(double const & x1, double const & x2, double const & y1, double const & y2);
double ENDF_integral_scheme_4(double const & x1, double const & x2, double const & y1, double const & y2);
double ENDF_integral_scheme_5(double const & x1, double const & x2, double const & y1, double const & y2);

double ENDF_integrate(double const & x1, double const & x2, double const & y1, double const & y2, int const scheme);
double ENDF_integrate_vector(double const & x1, double const & x2, std::vector<double> const & y_a, int const scheme);

#endif