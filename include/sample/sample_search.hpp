#ifndef MAVOR_SAMPLE_INTERPOLATIONS_H
#define MAVOR_SAMPLE_INTERPOLATIONS_H

#include <vector>
#include <string>
#include <iostream>

#include "predefined_coeff_evaluations.hpp"

typedef std::pair<size_t, size_t> InterpolationIndices;

InterpolationIndices findSampleInterpolationIndices(Iter begin, Iter end, double val);
InterpolationIndices findSampleCoeffInterpolationIndices(Iter begin, 
                                                         Iter end, 
                                                         double search_val, 
                                                         int num_coeffs, 
                                                         EvaluationFunction eval_func,
                                                         double eval_point);

#endif 
