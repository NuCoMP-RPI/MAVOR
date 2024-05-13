#include <iostream>
#include <vector>

#include "H5Cpp.h"

#include "sab_file.hpp"
#include "hdf5_file.hpp"

SabData::SabData(const std::string & file_path){
    H5::H5File file(file_path, H5F_ACC_RDONLY);

    readHDF5Int(file, "ZA", za);
    readHDF5Int(file, "MAT", mat);
    readHDF5Double(file, "Temp", temp);
    readHDF5Double(file, "T_EFF", t_eff);
    readHDF5Double(file, "TEMP_RATIO", temp_ratio);
    readHDF5Double(file, "A0", a0);
    readHDF5Double(file, "E_MAX", e_max);
    readHDF5Double(file, "M0", m0);
    readHDF5Double(file, "FREE_XS", free_xs);
    readHDF5Double(file, "BOUND_XS", bound_xs);
    readHDF5DoubleVector(file, "Incident Energy Grid", inc_energy_grid);
    readHDF5DoubleVector(file, "Incoherent Inelastic XS", ii_xs);
    readHDF5DoubleVector(file, "Beta CDF Grid", beta_cdf_grid);
    std::vector<double> fit_betas_vector;
    readHDF5DoubleVector(file, "Fit Betas", fit_betas_vector);
    fit_beta_vals = __vector_to_matrix__(fit_betas_vector, inc_energy_grid.size(), beta_cdf_grid.size());
    readHDF5DoubleVector(file, "Beta Grid", beta_grid);
    readHDF5DoubleVector(file, "Alpha CDF Grid", alpha_cdf_grid);
    std::vector<double> fit_alphas_vector;
    readHDF5DoubleVector(file, "Fit Alphas", fit_alphas_vector);
    fit_alpha_vals = __vector_to_matrix__(fit_alphas_vector, beta_grid.size(), alpha_cdf_grid.size());
}

std::vector<std::vector<double>> SabData::__vector_to_matrix__(std::vector<double> const & flat_vector, int const n_rows, int const n_cols){
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