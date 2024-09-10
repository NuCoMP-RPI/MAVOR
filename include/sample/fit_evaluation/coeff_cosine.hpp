#ifndef MAVOR_SAMPLE_EVAL_COSINE_H
#define MAVOR_SAMPLE_EVAL_COSINE_H

#include<vector>

double naive_cosine(double const & x, std::vector<double> const& coeffs);
double improved_cosine(double const & x, std::vector<double> const & coeffs);

#endif