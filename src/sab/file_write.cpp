#include <highfive/highfive.hpp>

#include "jagged.hpp"

#include "file_write.hpp"
#include "process_file.hpp"

/// @brief Flattens a jagged matrix and writes it to an HDF5 file.
/// This function flattens a jagged (2D) matrix and writes the flattened data and the row offsets to an HDF5 file. 
/// It uses the `flatten_jagged_matrix__` function to flatten the matrix, then stores both the flattened data and the offsets 
/// (starting indices of each row) as separate datasets in the given HDF5 file.
/// @tparam T The type of the elements in the matrix (e.g., int, float, etc.).
/// @param file The HDF5 file to which the data will be written.
/// @param data The jagged matrix to be flattened and written to the file.
/// @param name The base name used for the datasets in the file. The datasets are named with the base name 
///             followed by " Flattened" for the flattened data and " Offsets" for the offsets.
template<typename T>
void write_jagged_matrix__(HighFive::File file, const T &data, const std::string &name){
    auto [offsets, flat_data] = flatten_jagged_matrix__(data);
    file.createDataSet(name + " Flattened", flat_data);
    file.createDataSet(name + " Offsets", offsets);
}

void write_sampling_data(DistData const & sampling_data, std::string const & file_name){
    HighFive::File file(file_name, HighFive::File::Overwrite);

    file.createDataSet("ZA", sampling_data.tsl_data.za);
    file.createDataSet("MAT", sampling_data.tsl_data.mat);
    file.createDataSet("Temperature", sampling_data.tsl_data.temp);
    file.createDataSet("Effective Temperature", sampling_data.tsl_data.t_eff);
    file.createDataSet("Temperature Ratio", sampling_data.tsl_data.temp_ratio);
    file.createDataSet("A0", sampling_data.tsl_data.a0);
    file.createDataSet("Maximum Energy", sampling_data.tsl_data.e_max);
    file.createDataSet("M0", sampling_data.tsl_data.m0);
    file.createDataSet("Free XS", sampling_data.tsl_data.free_xs);
    file.createDataSet("Bound XS", sampling_data.tsl_data.bound_xs);

    file.createDataSet("Incident Energy Grid", sampling_data.incident_energy_grid);
    file.createDataSet("Incoherent Inelastic XS", sampling_data.cross_section);
    write_jagged_matrix__(file, sampling_data.beta_cdf_grid, "Beta CDF Grid");
    write_jagged_matrix__(file, sampling_data.beta_vals, "Betas");

    file.createDataSet("Beta Grid", sampling_data.beta_grid);
    write_jagged_matrix__(file, sampling_data.alpha_cdf_grid, "Alpha CDF Grid");
    write_jagged_matrix__(file, sampling_data.alpha_vals, "Alphas");
}
