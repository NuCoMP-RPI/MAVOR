#include <iostream>
#include <vector>

#include <highfive/highfive.hpp>

#include "sab_file.hpp"

template<typename T>
std::vector<std::vector<T>> read_jagged_matrix__(HighFive::File file, const std::string &name){
    std::vector<T> flat_data = file.getDataSet(name + " Flattened").read<std::vector<T>>();
    std::vector<int> offsets = file.getDataSet(name + " Offsets").read<std::vector<int>>();
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
    temp = file.getDataSet("Temperature").read<double>();
    t_eff = file.getDataSet("Effective Temperature").read<double>();
    temp_ratio = file.getDataSet("Temperature Ratio").read<double>();
    a0 = file.getDataSet("A0").read<double>();
    e_max = file.getDataSet("Maximum Energy").read<double>();
    m0 = file.getDataSet("M0").read<double>();
    free_xs = file.getDataSet("Free XS").read<double>();
    bound_xs = file.getDataSet("Bound XS").read<double>();

    inc_energy_grid = file.getDataSet("Incident Energy Grid"). read<std::vector<double>>();
    ii_xs = file.getDataSet("Incoherent Inelastic XS"). read<std::vector<double>>();

    std::vector<std::vector<double>> beta_cdf_grid_jagged = read_jagged_matrix__<double>(file, "Beta CDF Grid");
    if (is_uniform_matrix(beta_cdf_grid_jagged)){beta_cdf_grid = beta_cdf_grid_jagged[0];}
    else {throw std::runtime_error("Beta CDF Grids are not uniform.");}
    
    beta_vals = read_jagged_matrix__<double>(file, "Betas");

    beta_grid = file.getDataSet("Beta Grid").read<std::vector<double>>();

    std::vector<std::vector<double>> alpha_cdf_grid_jagged = read_jagged_matrix__<double>(file, "Alpha CDF Grid");
    if (is_uniform_matrix(alpha_cdf_grid_jagged)){alpha_cdf_grid = alpha_cdf_grid_jagged[0];}
    else {throw std::runtime_error("Alpha CDF Grids are not uniform.");}
    
    alpha_vals = read_jagged_matrix__<double>(file, "Alphas");
}