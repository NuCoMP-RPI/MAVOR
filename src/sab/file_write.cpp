#include "H5Cpp.h"

#include "file_write.hpp"
#include "process_file.hpp"

void __write_int__(H5::H5File file, int const & value, std::string const & value_name){
    hsize_t dims[1] = {1};
    H5::DataSpace dataspace(1, dims);
    H5::IntType datatype(H5::PredType::NATIVE_INT);
    H5::DataSet dataset = file.createDataSet(value_name, datatype, dataspace);
    dataset.write(&value, H5::PredType::NATIVE_INT);
}

void __write_double__(H5::H5File file, double const & value, std::string const & value_name){
    hsize_t dims[1] = {1};
    H5::DataSpace dataspace(1, dims);
    H5::FloatType datatype(H5::PredType::NATIVE_DOUBLE);
    H5::DataSet dataset = file.createDataSet(value_name, datatype, dataspace);
    dataset.write(&value, H5::PredType::NATIVE_DOUBLE);
}

void __write_vector__(H5::H5File file, std::vector<double> const & vector, std::string const & vector_name){
    hsize_t dims[1] = {vector.size()};
    H5::DataSpace dataspace(1, dims);
    H5::FloatType datatype(H5::PredType::NATIVE_DOUBLE);
    H5::DataSet dataset = file.createDataSet(vector_name, datatype, dataspace);
    dataset.write(vector.data(), H5::PredType::NATIVE_DOUBLE);
}

void __write_matrix__(H5::H5File file, std::vector<std::vector<double>> const & matrix, std::string const & matrix_name){
    hsize_t dims[2] = {matrix.size(), matrix[0].size()};
    H5::DataSpace dataspace(2, dims);
    H5::FloatType datatype(H5::PredType::NATIVE_DOUBLE);
    H5::DataSet dataset = file.createDataSet(matrix_name, datatype, dataspace);
    // Flatten matrix to be able to write
    // Don't think HDF5 supports vec<vec>> writing 
    std::vector<double> flattenedMatrix;
    for (const auto& row : matrix) {
        flattenedMatrix.insert(flattenedMatrix.end(), row.begin(), row.end());
    }
    dataset.write(flattenedMatrix.data(), H5::PredType::NATIVE_DOUBLE);
}

void write_sampling_data(DistData const & sampling_data, std::string const & file_name){
    H5::FileCreatPropList fcpl;
    H5::FileAccPropList fapl;
    H5::H5File file(file_name, H5F_ACC_TRUNC, fcpl, fapl);

    __write_int__(file, sampling_data.za, "ZA");
    __write_int__(file, sampling_data.mat, "MAT");
    __write_double__(file, sampling_data.temp, "Temp");
    __write_double__(file, sampling_data.t_eff, "T_EFF");
    __write_double__(file, sampling_data.temp_ratio, "TEMP_RATIO");
    __write_double__(file, sampling_data.a0, "A0");
    __write_double__(file, sampling_data.e_max, "E_MAX");
    __write_double__(file, sampling_data.m0, "M0");
    __write_double__(file, sampling_data.free_xs, "FREE_XS");
    __write_double__(file, sampling_data.bound_xs, "BOUND_XS");

    __write_vector__(file, sampling_data.inc_energy_grid, "Incident Energy Grid");
    __write_vector__(file, sampling_data.ii_xs, "Incoherent Inelastic XS");
    __write_vector__(file, sampling_data.beta_cdf_grid, "Beta CDF Grid");
    __write_matrix__(file, sampling_data.fit_beta_vals, "Fit Betas");

    __write_vector__(file, sampling_data.beta_grid, "Beta Grid");
    __write_vector__(file, sampling_data.alpha_cdf_grid, "Alpha CDF Grid");
    __write_matrix__(file, sampling_data.fit_alpha_vals, "Fit Alphas");

    file.close();
}
