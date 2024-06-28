#include <iostream>

#include "H5Cpp.h"

#include "sample_cdf.hpp"

#include "runtime_variables.hpp"
#include "hdf5_file.hpp"

CDFFile::CDFFile(std::string const & file_path){
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
    readHDF5DoubleVector(file, "Incident Energy Grid", inc_ener_grid);
    readHDF5DoubleVector(file, "Incoherent Inelastic XS", ii_xs);
    readHDF5DoubleVector(file, "Beta CDF Grid", beta_cdf_grid);
    readHDF5DoubleVector(file, "Fit Betas", fit_betas);
    readHDF5DoubleVector(file, "Beta Grid", beta_grid);
    readHDF5DoubleVector(file, "Alpha CDF Grid", alpha_cdf_grid);
    readHDF5DoubleVector(file, "Fit Alphas", fit_alphas);
}

void sample_cdf(){
    CDFFile data(sample_input_file);
}