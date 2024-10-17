#ifndef ARANGE_H
#define ARANGE_H

#include <vector>
#include <type_traits>

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
