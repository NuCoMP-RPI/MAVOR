#ifndef MAVOR_SAMPLE_EVAL_SINE_H
#define MAVOR_SAMPLE_EVAL_SINE_H

#include<vector>

double naive_sine_vec(double const & x, std::vector<double> const & coeffs);
double improved_sine_vec(double const & x, std::vector<double> const & coeffs);

typedef std::vector<double>::const_iterator Iter;

double naive_sine_iter(double const & x, Iter begin, Iter end);
double improved_sine_iter(double const & x, Iter begin, Iter end);

#endif