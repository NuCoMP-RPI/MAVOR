#ifndef MAVOR_HORNER_H
#define MAVOR_HORNER_H

#include <vector>

double horner(double const & f_x, std::vector<double> const & coeffs);

typedef std::vector<double>::const_iterator Iter;

double horner(double const & f_x, Iter begin, Iter end);

#endif