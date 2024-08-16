#ifndef MAVOR_INTERPOLATION_H
#define MAVOR_INTERPOLATION_H

#include <vector>

double ENDF_interp_scheme_1(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);
double ENDF_interp_scheme_2(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);
double ENDF_interp_scheme_3(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);
double ENDF_interp_scheme_4(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);
double ENDF_interp_scheme_5(double const & x1, double const & x2, double const & y1, double const & y2, double const& x);

double ENDF_interp(double const & x1, double const & x2, double const & y1, double const & y2, double const & x, int const scheme = 2);
double bi_interp(double const & x1, double const & x2, double const & y1, double const & y2, 
                 double const & f11, double const & f12, double const & f21, double const & f22, 
                 double const & x, double const & y, 
                 int const x_scheme = 2, int const y_scheme = 2);

// std::pair<size_t, size_t> findInterpolationIndexes(const std::vector<double>& array, double val);
std::pair<size_t, size_t> findInterpolationIndexes(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end, double val);
#endif