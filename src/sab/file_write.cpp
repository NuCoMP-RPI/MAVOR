#include <highfive/highfive.hpp>

#include "jagged.hpp"

#include "file_write.hpp"
#include "process_file.hpp"

/// @brief Flattens a jagged matrix and writes it to an HDF5 group.
/// This function flattens a jagged (2D) matrix and writes the flattened data and the row offsets to an HDF5 group. 
/// It uses the `flatten_jagged_matrix__` function to flatten the matrix, then stores both the flattened data and the offsets 
/// (starting indices of each row) as separate datasets in the given HDF5 group.
/// @tparam T The type of the elements in the matrix (e.g., int, float, etc.).
/// @param group The HDF5 group to which the data will be written.
/// @param data The jagged matrix to be flattened and written to the file.
/// @param name The base name used for the datasets in the file. The datasets are named with the base name 
///             followed by " Flattened" for the flattened data and " Offsets" for the offsets.
template<typename T>
void write_jagged_matrix__(HighFive::Group group, const T &data, const std::string &name){
    auto [offsets, flat_data] = flatten_jagged_matrix__(data);
    group.createDataSet(name + "_FLATTENED", flat_data);
    group.createDataSet(name + "_OFFSETS", offsets);
}

void write_sampling_data(DistData const & sampling_data, std::string const & file_name){
    HighFive::File file(file_name, HighFive::File::Overwrite);

    file.createDataSet("ZA", sampling_data.tsl_data.za);
    file.createDataSet("MAT", sampling_data.tsl_data.mat);
    file.createDataSet("A0", sampling_data.tsl_data.a0);
    file.createDataSet("E_MAX", sampling_data.tsl_data.e_max);
    file.createDataSet("M0", sampling_data.tsl_data.m0);
    file.createDataSet("BOUND_XS", sampling_data.tsl_data.bound_xs);
    file.createDataSet("FREE_XS", sampling_data.tsl_data.free_xs);
    file.createDataSet("TEMPERATURE", sampling_data.tsl_data.temp);
    file.createDataSet("T_EFF", sampling_data.tsl_data.t_eff);
    file.createDataSet("T_R", sampling_data.tsl_data.temp_ratio);

    HighFive::Group xs = file.createGroup("XS");
    xs.createDataSet("ENERGY_GRID", sampling_data.incident_energy_grid);
    xs.createDataSet("XS_VALUES", sampling_data.cross_section);

    HighFive::Group beta = file.createGroup("BETA");
    beta.createDataSet("ENERGY_GRID", sampling_data.incident_energy_grid);
    write_jagged_matrix__(beta, sampling_data.beta_cdf_grid, "CDF_GRID");
    write_jagged_matrix__(beta, sampling_data.beta_vals, "BETA_VALUES");

    HighFive::Group alpha = file.createGroup("ALPHA");
    alpha.createDataSet("BETA_GRID", sampling_data.beta_grid);
    write_jagged_matrix__(alpha, sampling_data.alpha_cdf_grid, "CDF_GRID");
    write_jagged_matrix__(alpha, sampling_data.alpha_vals, "ALPHA_VALUES");
}
