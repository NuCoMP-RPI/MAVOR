#ifndef MAVOR_SAMPLE_INTERPOLATIONS_H
#define MAVOR_SAMPLE_INTERPOLATIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <numeric>

#include "predefined_coeff_evaluations.hpp"

typedef std::pair<size_t, size_t> InterpolationIndices;

/**
 * @brief Finds the indices of list of elements that would bracket the search value val
 * @tparam Iter Constant iterator
 * @param begin Iterator pointing to the first element of the search range
 * @param end Iterator pointing to the last element of the search range
 * If you use x.end(), you need to subtract one from the iterator
 * @param val Double of the value that is desired to be found
 * @return InterpolationIndicies type (std::pair(size_t, size_t))
 */
template <typename Iter>
InterpolationIndices findSampleInterpolationIndices(const Iter &begin, const Iter &end, const double &val) 
{
    Iter lo = begin + 1; // +1 handles if below grid
    Iter hi = end;
    int len = std::distance(lo, hi);
    while (len > 0) {
        int half = len / 2;
        Iter mid = lo;
        std::advance(mid, half);
        if (*mid < val) {
            lo = mid;
            ++lo;
            len = len - half - 1;
        } else {
            len = half;
        }
    }
    size_t hi_index = std::distance(begin, lo);
    size_t lo_index = hi_index - 1;
    return std::make_pair(lo_index, hi_index);
}

/**
 * @brief Finds the indices of list of coefficients that would bracket the search value val.
 * This method uses std::inner_product to evaluate the coefficients.
 * @tparam Iter Constant iterator
 * @param begin Iterator pointing to the first coefficient in the first set of coefficients of the search range
 * @param end Iterator pointing to the first coefficient in the last set of coefficients of the search range
 * See test_sample_search.cpp to see how to set begin and end properly
 * @param val Double of the value that is desired to be found\
 * @param evaled_basis_points Evaluated f(x) values of the basis functions at the desired x value.  
 * This should be the returned vector from an Evaluation Function
 * @return InterpolationIndicies type (std::pair(size_t, size_t))
 */
template <typename Iter>
InterpolationIndices findSampleCoeffInterpolationIndices(const Iter &begin, 
                                                         const Iter &end, 
                                                         const double &val, 
                                                         const std::vector<double> &evaled_basis_points)
{
    int num_coeffs = evaled_basis_points.size();
    Iter lo = begin + num_coeffs; // +num_coeffs handles if below grid
    Iter hi = end;
    int len = std::distance(lo, hi) / num_coeffs;
    while (len > 0) {
        int half = len / 2;
        Iter mid = lo;
        std::advance(mid, half * num_coeffs);
        double func_val = std::inner_product(mid, mid + num_coeffs, evaled_basis_points.begin(), 0.0);
        if (func_val < val) {
            lo = mid;
            lo += num_coeffs;
            len = len - half - 1;
        } else {
            len = half;
        }
    }
    size_t hi_index = std::distance(begin, lo) / num_coeffs;
    size_t lo_index = hi_index - 1;
    return std::make_pair(lo_index, hi_index);
}

#endif 
