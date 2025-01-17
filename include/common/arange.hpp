#ifndef ARANGE_H
#define ARANGE_H

#include <vector>
#include <type_traits>

/// @brief Generates a sequence of values from start to stop with a given step size.
/// @tparam T The numeric type of the values in the sequence. Must be an arithmetic type.
/// @param start The starting value of the sequence (inclusive).
/// @param stop The end value of the sequence (exclusive).
/// @param step The difference between consecutive values in the sequence. Must be non-zero.
/// @return A std::vector<T> containing the generated sequence of values.
template <typename T>
std::vector<T> arange(T start, T stop, T step) {
    static_assert(std::is_arithmetic<T>::value, "Type must be numeric");    
    std::vector<T> result;
    for (T val = start; val < stop; val += step) {
        result.push_back(val);
    }
    return result;
}

#endif
