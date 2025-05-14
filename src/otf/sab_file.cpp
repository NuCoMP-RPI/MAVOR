#include <iostream>
#include <vector>

#include <highfive/highfive.hpp>

#include "sab_file.hpp"

template<typename T>
std::vector<std::vector<T>> read_jagged_matrix__(HighFive::Group group, const std::string &name){
    std::vector<T> flat_data = group.getDataSet(name + "_FLATTENED").read<std::vector<T>>();
    std::vector<int> offsets = group.getDataSet(name + "_OFFSETS").read<std::vector<int>>();
    std::vector<std::vector<T>> reconstructed;
    for (size_t i = 0; i < offsets.size() - 1; i++) {
        reconstructed.push_back(std::vector<T>(
            flat_data.begin() + offsets[i], flat_data.begin() + offsets[i + 1]
        ));
    }
    return reconstructed;
}

template<typename T>
bool is_uniform_matrix(const std::vector<std::vector<T>> &matrix){
    if (matrix.empty()) return true;
    const std::vector<T>& first_row = matrix[0];
    for (const auto& row : matrix) {
        if (row.size() != first_row.size()) {return false;}
        if (row != first_row) {return false;}
    }
    return true;
}

SabData::SabData(const std::string & file_path){
    HighFive::File file(file_path, HighFive::File::ReadOnly);

    za = file.getDataSet("ZA").read<int>();
    mat = file.getDataSet("MAT").read<int>();
    a0 = file.getDataSet("A0").read<double>();
    e_max = file.getDataSet("E_MAX").read<double>();
    m0 = file.getDataSet("M0").read<double>();
    bound_xs = file.getDataSet("BOUND_XS").read<double>();
    free_xs = file.getDataSet("FREE_XS").read<double>();
    temp = file.getDataSet("TEMPERATURE").read<double>();
    t_eff = file.getDataSet("T_EFF").read<double>();
    temp_ratio = file.getDataSet("T_R").read<double>();

    HighFive::Group xs = file.getGroup("XS");
    inc_energy_grid = xs.getDataSet("ENERGY_GRID"). read<std::vector<double>>();
    ii_xs = xs.getDataSet("XS_VALUES"). read<std::vector<double>>();

    HighFive::Group beta = file.getGroup("BETA");
    std::vector<std::vector<double>> beta_cdf_grid_jagged = read_jagged_matrix__<double>(beta, "CDF_GRID");
    if (is_uniform_matrix(beta_cdf_grid_jagged)){beta_cdf_grid = beta_cdf_grid_jagged[0];}
    else {throw std::runtime_error("Beta CDF Grids are not uniform.");}
    beta_vals = read_jagged_matrix__<double>(beta, "BETA_VALUES");

    HighFive::Group alpha = file.getGroup("ALPHA");
    beta_grid = alpha.getDataSet("BETA_GRID").read<std::vector<double>>();
    std::vector<std::vector<double>> alpha_cdf_grid_jagged = read_jagged_matrix__<double>(alpha, "CDF_GRID");
    if (is_uniform_matrix(alpha_cdf_grid_jagged)){alpha_cdf_grid = alpha_cdf_grid_jagged[0];}
    else {throw std::runtime_error("Alpha CDF Grids are not uniform.");}
    alpha_vals = read_jagged_matrix__<double>(alpha, "ALPHA_VALUES");
}