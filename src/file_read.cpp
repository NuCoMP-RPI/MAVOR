#include <iostream>
#include <vector>
#include <algorithm>

#include "H5Cpp.h"

#include "file_read.hpp"

// Class Constructor
TslData::TslData(const std::string& file_path)
{
    H5::H5Library::open();
    H5::H5File file(file_path, H5F_ACC_RDONLY);

    readHDF5Int(file, "lat", lat);
    readHDF5Int(file, "lasym", lasym);
    readHDF5Int(file, "lln", lln);
    readHDF5Int(file, "za", za);
    readHDF5Int(file, "mat", mat);
    readHDF5Double(file, "temp", temp);
    readHDF5Double(file, "t_eff", t_eff);
    readHDF5Double(file, "temp_ratio", temp_ratio);
    readHDF5Double(file, "a0", a0);
    readHDF5Double(file, "e_max", e_max);
    readHDF5Double(file, "m0", m0);
    readHDF5Double(file, "free_xs", free_xs);
    readHDF5Double(file, "bound_xs", bound_xs);
    readHDF5DoubleArray(file, "alphas", alphas);
    readHDF5DoubleArray(file, "betas", betas);
    readHDF5DoubleArray(file, "tsl_vals", tsl_vals_array);
    tsl_vals = __vector_to_matrix__(tsl_vals_array, betas.size(), alphas.size());
    
    file.close();
    H5::H5Library::close();
}

// Private Methods //
// File reading

void TslData::readHDF5DoubleArray(H5::H5File& file, const std::string& datasetName, std::vector<double>& array) {
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    // Fancy stuff is here to allow reading matrices into a vector
    // HDF5 does not support reading directly into nested vectors
    int rank = dataspace.getSimpleExtentNdims();
    hsize_t dims[rank];
    dataspace.getSimpleExtentDims(dims);
    hsize_t totalSize = 1;
    for (int i = 0; i < rank; ++i) {
        totalSize *= dims[i];
    }
    array.resize(totalSize);
    dataset.read(array.data(), H5::PredType::NATIVE_DOUBLE);
    dataset.close();
    dataspace.close();
}

void TslData::readHDF5Double(H5::H5File& file, const std::string& datasetName, double& value){
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    dataset.read(&value, H5::PredType::NATIVE_DOUBLE);
    dataset.close();
    dataspace.close();
}

void TslData::readHDF5Int(H5::H5File& file, const std::string& datasetName, int& value){
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    dataset.read(&value, H5::PredType::NATIVE_INT);
    dataset.close();
    dataspace.close();
}

// Supporting data methods

void TslData::__vec_element_mult__(std::vector<double>&vec, double const val){
    for(int i = 0; i<vec.size(); i++) vec[i] *= val;
}

std::vector<std::vector<double>> TslData::__vector_to_matrix__(std::vector<double> const & flat_vector, int const n_rows, int const n_cols){
    // sanity check
    if(n_rows*n_cols != flat_vector.size()){
        throw std::domain_error("Length of the vector does not match the n_rows*n_cols");
    }
    std::vector<std::vector<double>> matrix;
    const auto begin = std::begin(flat_vector);
    for(std::size_t row = 0 ; row < n_rows; ++row){ 
        matrix.push_back({begin + row*n_cols, begin + (row+1)*n_cols});
    }
    return matrix;
}

std::vector<double> TslData::__vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
    std::vector<double> new_vec(vec);
    if(del_duplicate){
        new_vec.erase(new_vec.begin());
    }
    std::reverse(new_vec.begin(), new_vec.end());
    for(auto val: vec){
        new_vec.push_back(val);
    }
    return new_vec;
}

std::vector<double> TslData::__negative_vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
    std::vector<double> new_vec(vec);
    if(del_duplicate){
        new_vec.erase(new_vec.begin());
    }
    std::reverse(new_vec.begin(), new_vec.end());
    __vec_element_mult__(new_vec, -1);
    for(auto val: vec){
        new_vec.push_back(val);
    }
    return new_vec;
}

std::vector<std::vector<double>> TslData::__matrix_2d_flip__(std::vector<std::vector<double>> const & matrix2d, bool const del_duplicate, int const axis){
    std::vector<std::vector<double>> result = matrix2d;
    if (axis == 0) {
        std::reverse(result.begin(), result.end()); // Flip along rows
    } else if (axis == 1) {
        for (auto& row : result) {
            std::reverse(row.begin(), row.end()); // Flip along columns
        }
    } else {
        std::cerr << "Invalid axis value. Only 0 (rows) and 1 (columns) are supported." << std::endl;
    }
    return result;
}

std::vector<double> TslData::__lat_scale__(std::vector<double> const & vec, double const ref_temp){
    std::vector<double> new_vec(vec);
    if ( lat == 1 ) {
        __vec_element_mult__(new_vec, ref_temp/temp);
    } 
    return new_vec;
}

// Public Methods //
// Alpha and Betas

std::vector<double> TslData::return_scaled_alphas(double const & ref_temp){
    return __lat_scale__(alphas);
}

std::vector<double> TslData::return_scaled_betas(double const & ref_temp){
    return __lat_scale__(betas);
}

std::vector<double> TslData::return_full_betas(){
   return __negative_vector_mirror__(betas, betas[0] == 0); 
}

std::vector<double> TslData::return_full_scaled_betas(double const & ref_temp){
    return __negative_vector_mirror__(__lat_scale__(betas), betas[0] == 0);
}


// TSL Values

std::vector<std::vector<double>> TslData:: return_tsl_vals(){
std::vector<std::vector<double>> new_mat;
return new_mat;
}

std::vector<std::vector<double>> TslData:: return_half_sym_tsl_vals(){
std::vector<std::vector<double>> new_mat;
return new_mat;
}

std::vector<std::vector<double>> TslData:: return_half_asym_tsl_vals(){
std::vector<std::vector<double>> new_mat;
return new_mat;
}

std::vector<std::vector<double>> TslData:: return_full_sym_tsl_vals(){
std::vector<std::vector<double>> new_mat;
return new_mat;
}

std::vector<std::vector<double>> TslData:: return_full_asym_tsl_vals(){
std::vector<std::vector<double>> new_mat;
return new_mat;
}