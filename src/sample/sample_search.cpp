#include <vector>
#include <iostream>

#include "predefined_coeff_evaluations.hpp"

#include "sample_search.hpp"

// InterpolationIndices findSampleInterpolationIndexes(Iter begin, Iter end, double val) {
//     auto it = std::lower_bound(begin + 1, end, val); // +1 handles if below grid
//     size_t hi_index = std::distance(begin, it);
//     hi_index = (hi_index == std::distance(begin, end)) ? hi_index - 1 : hi_index; // -1 handles if above grid
//     size_t lo_index = hi_index - 1;
//     return std::make_pair(lo_index, hi_index);
// }

InterpolationIndices findSampleInterpolationIndices(Iter begin, Iter end, double val){
    Iter lo = begin + 1; // +1 handles if below grid
    Iter hi = end;
    int len = std::distance(lo, hi);
    while (len > 0){
        int half = len / 2;
        Iter mid = lo;
        std::advance(mid, half);
        if (*mid < val){
            lo = mid;
            ++lo;
            len = len - half - 1;
        }
        else len = half;
    }
    size_t hi_index = std::distance(begin, lo);
    hi_index = (hi_index == std::distance(begin, end)) ? hi_index - 1 : hi_index; // -1 handles if above grid
    size_t lo_index = hi_index - 1;
    return std::make_pair(lo_index, hi_index);
}

InterpolationIndices findSampleCoeffInterpolationIndices(Iter begin, 
                                                         Iter end, 
                                                         double search_val, 
                                                         int num_coeffs, 
                                                         EvaluationFunction eval_func,
                                                         double eval_point){
    Iter lo = begin + num_coeffs; // +num_coeffs (+1 index) handles if below grid
    Iter hi = end;
    int len = std::distance(lo, hi)/num_coeffs;
    while (len>0){
        int half = len / 2;
        Iter mid = lo;
        std::advance(mid, half*num_coeffs);
        double func_val = eval_func.function(eval_point, mid, mid+num_coeffs);
        if (func_val < search_val){
            lo = mid;
            lo += num_coeffs;
            len = len - half - 1;
        }
        else len = half;
    }
    size_t hi_index = std::distance(begin, lo)/num_coeffs;
    hi_index = (hi_index == std::distance(begin, end)/num_coeffs) ? hi_index - 1 : hi_index; // -1 handles if above grid
    size_t lo_index = hi_index - 1;
    return std::make_pair(lo_index, hi_index);
}