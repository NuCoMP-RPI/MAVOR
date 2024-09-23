#ifndef MAVOR_SAMPLE_EVAL_COSINE_H
#define MAVOR_SAMPLE_EVAL_COSINE_H

#include<vector>

double naive_cosine_vec(double const & x, std::vector<double> const & coeffs);
double improved_cosine_vec(double const & x, std::vector<double> const & coeffs);

typedef std::vector<double>::const_iterator Iter;

double naive_cosine_iter(double const & x, Iter begin, Iter end);
double improved_cosine_iter(double const & x, Iter begin, Iter end);

#endif