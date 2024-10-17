#ifndef LINSPACE_H
#define LINSPACE_H

#include <vector>
#include <type_traits>

template <typename T>
std::vector<T> linspace(T start, T stop, int num) {
    static_assert(std::is_arithmetic<T>::value, "Type must be numeric");
    
    std::vector<T> result;
    if (num == 1) {
        result.push_back(start);
    } else {
        T step = (stop - start) / static_cast<T>(num - 1);
        for (int i = 0; i < num; ++i) {
            result.push_back(start + i * step);
        }
    }
    return result;
}

#endif
