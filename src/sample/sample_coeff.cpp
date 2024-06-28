#include <iostream>
#include <vector>

#include "sample_coeff.hpp"

#include "runtime_variables.hpp"
#include "hdf5_file.hpp"
#include "predefined_fit_settings.hpp"

CoeffFile::CoeffFile(std::string const & file_path){
    H5::H5File file(file_path, H5F_ACC_RDONLY);

    readHDF5Int(file, "ZA", za);
    readHDF5Int(file, "MAT", mat);
    readHDF5Double(file, "A0", a0);
    readHDF5Double(file, "E_MAX", e_max);
    readHDF5Double(file, "M0", m0);
    readHDF5Double(file, "FREE_XS", free_xs);
    readHDF5Double(file, "BOUND_XS", bound_xs);
    
    readHDF5Bool(file, "Scale XS temperatures", xs_scale_temperatures);
    readHDF5Double(file, "XS Minimum Scaled Value", xs_scale_minimum);
    readHDF5Double(file, "XS Maximum Scaled Value", xs_scale_maximum);
    readHDF5String(file, "XS Fitting Function", xs_basis_function_string);
    set_basis_function__(xs_basis_function, xs_basis_function_string);

    readHDF5Bool(file, "Scale BETA temperatures", beta_scale_temperatures);
    readHDF5Double(file, "BETA Minimum Scaled Value", beta_scale_minimum);
    readHDF5Double(file, "BETA Maximum Scaled Value", beta_scale_maximum);
    readHDF5String(file, "BETA Fitting Function", beta_basis_function_string);
    set_basis_function__(beta_basis_function, beta_basis_function_string);

    readHDF5Bool(file, "Scale ALPHA temperatures", alpha_scale_temperatures);
    readHDF5Double(file, "ALPHA Minimum Scaled Value", alpha_scale_minimum);
    readHDF5Double(file, "ALPHA Maximum Scaled Value", alpha_scale_maximum);
    readHDF5String(file, "ALPHA Fitting Function", alpha_basis_function_string);
    set_basis_function__(alpha_basis_function, alpha_basis_function_string);

    readHDF5DoubleVector(file, "Incident Energy Grid", inc_ener_grid);
    readHDF5DoubleVector(file, "Beta CDF Grid", beta_cdf_grid);
    readHDF5DoubleVector(file, "Beta Grid", beta_grid);
    readHDF5DoubleVector(file, "Alpha CDF Grid", alpha_cdf_grid);

    readHDF5DoubleVector(file, "XS_Coefficients", ii_xs_coeffs);
    readHDF5DoubleVector(file, "Beta Coefficients", beta_coeffs);
    readHDF5DoubleVector(file, "Alpha Coefficients", alpha_coeffs);
}

void CoeffFile::set_basis_function__(BasisFunction & basis_func, std::string const& basis_func_string){
    for (auto const& [key, val]: basis_functions){
        if (val.first == basis_func_string){
            if (!silence){std::cout << "I found the basis function | " << basis_func_string << std::endl;}
            basis_func = val;
            return;
        }
    }
    throw std::out_of_range("Basis function was not found.");
}

void sample_coeff(){
    CoeffFile data(sample_input_file);
}