#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include "H5Cpp.h"

#include "file_read.hpp"
#include "runtime_variables.hpp"
#include "hdf5_file.hpp"

// Class Constructor
TslFileData::TslFileData(const std::string& file_path)
{
    H5::H5File file(file_path, H5F_ACC_RDONLY);

    readHDF5Int(file, "lat", lat);
    readHDF5Int(file, "lasym", lasym);
    readHDF5Int(file, "lln", lln);
    readHDF5Int(file, "za", za);
    readHDF5Int(file, "mat", mat);
    predefined_energy_grid_key = mat;
    readHDF5Double(file, "temp", temp);
    readHDF5Double(file, "t_eff", t_eff);
    readHDF5Double(file, "temp_ratio", temp_ratio);
    readHDF5Double(file, "a0", a0);
    readHDF5Double(file, "e_max", e_max);
    readHDF5Double(file, "m0", m0);
    readHDF5Double(file, "free_xs", free_xs);
    readHDF5Double(file, "bound_xs", bound_xs);
    readHDF5DoubleVector(file, "alphas", alphas);
    readHDF5DoubleVector(file, "betas", betas);
    readHDF5DoubleVector(file, "tsl_vals", tsl_vals_array);
    tsl_vals = __vector_to_matrix__(tsl_vals_array, betas.size(), alphas.size());
    
    file.close();
}

// Private Methods //
// Supporting data methods

void TslFileData::__vec_element_mult__(std::vector<double>&vec, double const val){
    for(int i = 0; i<vec.size(); i++){
        vec[i] *= val;
    }
}

void TslFileData::__matrix_element_exp__(std::vector<std::vector<double>>&matrix){
    for(auto& vec: matrix){
        for(int i = 0; i<vec.size(); i++){
            vec[i] = std::exp(vec[i]);
        }
    }
}

std::vector<std::vector<double>> TslFileData::__vector_to_matrix__(std::vector<double> const & flat_vector, int const n_rows, int const n_cols){
    if(n_rows*n_cols != flat_vector.size()){
        throw std::domain_error("Length of the vector does not match the n_rows*n_cols");
    }
    std::vector<std::vector<double>> matrix;
    const auto begin = std::begin(flat_vector);
    for(std::size_t row = 0 ; row<n_rows; ++row){ 
        matrix.push_back({begin + row*n_cols, begin + (row+1)*n_cols});
    }
    return matrix;
}

std::vector<double> TslFileData::__vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
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

std::vector<double> TslFileData::__negative_vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
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

std::vector<std::vector<double>> TslFileData::__matrix_2d_mirror__(std::vector<std::vector<double>> const & matrix2d, bool const del_duplicate){
    std::vector<std::vector<double>> result(matrix2d);
    if(del_duplicate){
        result.erase(result.begin());
    }
    std::reverse(result.begin(), result.end());
    for(auto vec: matrix2d){
        result.push_back(vec);
    }
    return result;
}


std::vector<double> TslFileData::__lat_scale__(std::vector<double> const & vec, double const ref_temp){
    std::vector<double> new_vec(vec);
    if (lat == 1){
        __vec_element_mult__(new_vec, ref_temp/temp);
    } 
    return new_vec;
}

// Public Methods //
// Alpha and Betas

std::vector<double> TslFileData::return_scaled_alphas(double const & ref_temp){
    return __lat_scale__(alphas);
}

std::vector<double> TslFileData::return_betas(){
    return betas;
}

std::vector<double> TslFileData::return_scaled_betas(double const & ref_temp){
    return __lat_scale__(betas);
}

std::vector<double> TslFileData::return_full_betas(){
   return __negative_vector_mirror__(betas, betas[0] == 0); 
}

std::vector<double> TslFileData::return_full_scaled_betas(double const & ref_temp){
    return __negative_vector_mirror__(__lat_scale__(betas), betas[0] == 0);
}


// TSL Values

std::vector<std::vector<double>> TslFileData::return_tsl_vals(){
    std::vector<std::vector<double>> new_mat(tsl_vals);
    if (lln != 0){
        __matrix_element_exp__(new_mat);
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_half_sym_tsl_vals(){
    std::vector<std::vector<double>> new_mat(return_tsl_vals());
    std::vector<double> temp_betas = return_scaled_betas();
    __vec_element_mult__(temp_betas, 0.5);
    if (lasym != 0){
        for(int i = 0; i<new_mat.size(); i++){
            __vec_element_mult__(new_mat[i], std::exp(temp_betas[i]/2));
        }
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_half_asym_tsl_vals(){
    std::vector<std::vector<double>> new_mat(return_tsl_vals());
    std::vector<double> temp_betas = return_scaled_betas();
    __vec_element_mult__(temp_betas, 0.5);
    if (lasym == 0){
        for(int i = 0; i<new_mat.size(); i++){
            __vec_element_mult__(new_mat[i], std::exp(-temp_betas[i]));
        }
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_full_sym_tsl_vals(){
    return __matrix_2d_mirror__(return_half_sym_tsl_vals(), betas[0] == 0); 
}

std::vector<std::vector<double>> TslFileData::return_full_asym_tsl_vals(){
    std::vector<std::vector<double>> new_mat = return_full_sym_tsl_vals();
    std::vector<double> temp_betas = return_full_scaled_betas();
    __vec_element_mult__(temp_betas, 0.5);
    for(int i = 0; i<new_mat.size(); i++){
        __vec_element_mult__(new_mat[i], std::exp(-temp_betas[i]));
    }
    return new_mat;
}