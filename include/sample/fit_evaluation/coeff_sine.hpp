#ifndef MAVOR_SAMPLE_EVAL_SINE_H
#define MAVOR_SAMPLE_EVAL_SINE_H

#include<vector>

double naive_sine(double const & x, std::vector<double> const& coeffs);
double improved_sine(double const & x, std::vector<double> const & coeffs);

#endif