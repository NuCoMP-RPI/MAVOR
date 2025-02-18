#ifndef JAGGED_H
#define JAGGED_H

#include <vector>

/// @brief Flattens a jagged (2D) matrix into a 1D vector and computes the offsets for each row.
/// This function takes a 2D vector (`std::vector<std::vector<T>>`) as input, where each inner vector represents a row of the jagged matrix.
/// It flattens the matrix into a single 1D vector (`std::vector<T>`) and computes the offsets (starting index of each row in the flattened data).
/// The result is returned as a pair of vectors:
/// - The first vector contains the offsets (starting indices of each row in the flattened vector).
/// - The second vector contains the flattened data.
/// @tparam T The type of the elements in the matrix (e.g., int, float, etc.).
/// @param mat The jagged matrix represented as a vector of vectors.
/// @return A pair of vectors:
/// - A vector of integers representing the starting indices of each row in the flattened data.
/// - A vector containing the flattened 1D data.
template<typename T>
std::pair<std::vector<int>, std::vector<T>> flatten_jagged_matrix__(const std::vector<std::vector<T>> &mat){
    std::vector<T> flat_data;
    std::vector<int> offsets = {0};
    for (const auto& vec : mat) {
        flat_data.insert(flat_data.end(), vec.begin(), vec.end());
        offsets.push_back(flat_data.size());
    }
    return std::make_pair(offsets, flat_data);
}

#endif