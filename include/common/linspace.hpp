#ifndef LINSPACE_H
#define LINSPACE_H

#include <vector>
#include <type_traits>

/// @brief Generates a linearly spaced vector of values.
///
/// This function generates a vector of values starting at `start` and ending at `stop`,
/// with a specified number of points (`num`). The values are spaced evenly between
/// `start` and `stop`, inclusive.
///
/// @tparam T The type of the values (must be numeric).
/// @param start The starting value of the range.
/// @param stop The ending value of the range.
/// @param num The number of points to generate.
/// @return A vector of type `T` containing the linearly spaced values.
///
/// @note If `num` is 1, only the `start` value is returned.
/// @note The function uses a static assertion to ensure that `T` is a numeric type.
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
