#include <iostream>
#include <vector>
#include <filesystem>
#include <map>

#include "Eigen/Dense"
#include "H5Cpp.h"

#include "process_otf.hpp"
#include "sab_file.hpp"
#include "scale_basis.hpp"
#include "runtime_variables.hpp"
#include "hdf5_file.hpp"

#include "predefined_fit_settings.hpp"

void __write_xs_Coeffs__(H5::H5File file, std::vector<Eigen::VectorXd> const & matrix, std::string const & matrix_name){
    hsize_t dims[2] = {matrix.size(), static_cast<hsize_t>(matrix[0].size())};
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

void __write_fit_Coeffs__(H5::H5File file, std::vector<std::vector<Eigen::VectorXd>> const & matrix, std::string const & matrix_name){
    hsize_t dims[3] = {matrix.size(), matrix[0].size(), static_cast<hsize_t>(matrix[0][0].size())};
    H5::DataSpace dataspace(3, dims);
    H5::FloatType datatype(H5::PredType::NATIVE_DOUBLE);
    H5::DataSet dataset = file.createDataSet(matrix_name, datatype, dataspace);
    // Flatten matrix to be able to write
    // Don't think HDF5 supports vec<vec>> writing 
    std::vector<double> flattenedMatrix;
    for (const auto& row : matrix) {
        for (const auto& col : row){
            flattenedMatrix.insert(flattenedMatrix.end(), col.begin(), col.end());
        }
    }
    dataset.write(flattenedMatrix.data(), H5::PredType::NATIVE_DOUBLE);
}

OTFData::OTFData(const std::string & directory){
    std::map<double, SabData, std::less<double>> files;
    for (const auto & entry : std::filesystem::directory_iterator(directory)){
        if (entry.is_regular_file()){
            SabData file_data(entry.path());
            files.insert(std::make_pair(file_data.temp, file_data));
        }
    }
    size_t num_files = files.size();

    // Extract the first files contents that should be the same across all files
    int k = 0;
    auto it = files.begin();
    za = it->second.za;
    mat = it->second.mat;
    a0 = it->second.a0;
    e_max = it->second.e_max;
    m0 = it->second.m0;
    free_xs = it->second.free_xs;
    bound_xs = it->second.bound_xs;
    inc_energy_grid = it->second.inc_energy_grid;
    beta_cdf_grid = it->second.beta_cdf_grid;
    beta_grid= it->second.beta_grid;
    alpha_cdf_grid = it->second.alpha_cdf_grid;

    // Initialize temp vector
    temps.resize(num_files);
    temps[k] = it->second.temp;

    // Initialize xs vector
    ii_xs.resize(inc_energy_grid.size(), Eigen::VectorXd(num_files));

    // Initialize xs coefficient vector
    xs_coeffs.resize(inc_energy_grid.size(), Eigen::VectorXd(xs_num_coeffs));

    // Initialize the vectors for storing the fit values (ordering needs to be <g1, g2, temps>)
    fit_beta_vals.resize(inc_energy_grid.size(), std::vector<Eigen::VectorXd>(beta_cdf_grid.size(), Eigen::VectorXd(num_files)));
    fit_alpha_vals.resize(beta_grid.size(), std::vector<Eigen::VectorXd>(alpha_cdf_grid.size(), Eigen::VectorXd(num_files)));

    // Initialize the vectors for storing the coefficients (ordering needs to be <g1, g2, coeffs>)
    beta_coeffs.resize(inc_energy_grid.size(), std::vector<Eigen::VectorXd>(beta_cdf_grid.size(), Eigen::VectorXd(beta_num_coeffs)));
    alpha_coeffs.resize(beta_grid.size(), std::vector<Eigen::VectorXd>(alpha_cdf_grid.size(), Eigen::VectorXd(alpha_num_coeffs)));

    // load in beta vals and xs
    for (int i = 0; i<inc_energy_grid.size(); i++){
        ii_xs[i][k] = it->second.ii_xs[i];
        for (int j = 0; j<beta_cdf_grid.size(); j++){
            fit_beta_vals[i][j][k] = it->second.fit_beta_vals[i][j];
        }
    }

    // load in alpha vals
    for (int i = 0; i<beta_grid.size(); i++){
        for (int j = 0; j<alpha_cdf_grid.size(); j++){
            fit_alpha_vals[i][j][k] = it->second.fit_alpha_vals[i][j];
        }
    }

    // increment counters
    it++;
    k++;

    // Read in the rest of the data
    while (it !=files.end())
    {
        __check__(za, it->second.za, "ZA");
        __check__(mat, it->second.mat, "MAT");
        __check__(a0, it->second.a0, "A0");
        __check__(e_max, it->second.e_max, "E_MAX");
        __check__(m0, it->second.m0, "M0");
        __check__(free_xs, it->second.free_xs, "FREE_XS");
        __check__(bound_xs, it->second.bound_xs, "BOUND_XS");
        __check__(inc_energy_grid, it->second.inc_energy_grid, "INCIDENT ENERGY GRID");
        __check__(beta_cdf_grid, it->second.beta_cdf_grid, "BETA CDF GRID");
        __check__(beta_grid, it->second.beta_grid, "BETA GRID");
        __check__(alpha_cdf_grid, it->second.alpha_cdf_grid, "ALPHA CDF GRID");
        temps[k] = it->second.temp;
        // load in beta vals
        for (int i = 0; i<inc_energy_grid.size(); i++){
            ii_xs[i][k] = it->second.ii_xs[i];
            for (int j = 0; j<beta_cdf_grid.size(); j++){
                fit_beta_vals[i][j][k] = it->second.fit_beta_vals[i][j];
            }
        }

        // load in alpha vals
        for (int i = 0; i<beta_grid.size(); i++){
            for (int j = 0; j<alpha_cdf_grid.size(); j++){
                fit_alpha_vals[i][j][k] = it->second.fit_alpha_vals[i][j];
            }
        }
        it++;
        k++;
    }

    // Load in the fit settings
    load_material_fits__();
    override_fit_settings__();
}

void OTFData::load_material_fits__(){
    PredefinedFitGroups::iterator fit_group_it = predefined_material_fits_groups.find(fit_group);
    if (fit_group_it != predefined_material_fits_groups.end()){
        PredefinedMaterialFitsMap::iterator mat_it = fit_group_it->second.find(mat);
        if (mat_it != fit_group_it->second.end()){
            MaterialFitSettings mat_fit_settings = mat_it->second;
            std::string mat_name = std::get<0>(mat_fit_settings);
            MaterialFit mat_fits = std::get<1>(mat_fit_settings);
            class_xs_fit = std::get<0>(mat_fits);
            class_beta_fit = std::get<1>(mat_fits);
            class_alpha_fit = std::get<2>(mat_fits);
        }
        else{load_default_fits__();};
    }
    else{load_default_fits__();};
}

void OTFData::load_default_fits__(){
    class_xs_fit = default_fit;
    class_beta_fit = default_fit;
    class_alpha_fit = default_fit;
}

void OTFData::override_fit_settings__(){
    if (basic_xs_fit_override){
        FittingFunctionMap::iterator fit_it = fitting_functions.find(user_predefined_xs_fit);
        if (fit_it != fitting_functions.end()) {
            if (!silence){std::cout << "Found the predefined fit for XS." << std::endl;}
            class_xs_fit = {fit_it->second, user_predefined_xs_num_coeffs};
        } 
        else {throw std::range_error("Predefined XS fit unknown.");}
    }

    if (full_xs_fit_override)
    {
        if(xs_override_num_coeffs){class_xs_fit.second = xs_num_coeffs;}
        if(xs_override_scale_temp){std::get<0>(class_xs_fit.first.second) = xs_scale_temp;}
        if(xs_override_temp_scale_min){std::get<1>(class_xs_fit.first.second) = xs_temp_scale_min;}
        if(xs_override_temp_scale_max){std::get<2>(class_xs_fit.first.second) = xs_temp_scale_max;}
        if(xs_override_fit_function){
            BasisFunctionMap::iterator basis_it = basis_functions.find(xs_basis_function);
            if (basis_it != basis_functions.end()){std::get<3>(class_xs_fit.first.second) = basis_it->second;}
            else {throw std::range_error("Unknown XS fitting function.");}
        }
    }    
    
    if (basic_beta_fit_override){
        FittingFunctionMap::iterator fit_it = fitting_functions.find(user_predefined_beta_fit);
        if (fit_it != fitting_functions.end()) {
            if (!silence){std::cout << "Found the predefined fit for BETA." << std::endl;}
            class_beta_fit = {fit_it->second, user_predefined_beta_num_coeffs};
        } 
        else {throw std::range_error("Predefined BETA fit unknown.");}
    }

    if (full_beta_fit_override)
    {
        if(beta_override_num_coeffs){class_beta_fit.second = beta_num_coeffs;}
        if(beta_override_scale_temp){std::get<0>(class_beta_fit.first.second) = beta_scale_temp;}
        if(beta_override_temp_scale_min){std::get<1>(class_beta_fit.first.second) = beta_temp_scale_min;}
        if(beta_override_temp_scale_max){std::get<2>(class_beta_fit.first.second) = beta_temp_scale_max;}
        if(beta_override_fit_function){
            BasisFunctionMap::iterator basis_it = basis_functions.find(beta_basis_function);
            if (basis_it != basis_functions.end()){std::get<3>(class_beta_fit.first.second) = basis_it->second;}
            else {throw std::range_error("Unknown BETA fitting function.");}
        }
    }
    
    if (basic_alpha_fit_override){
        FittingFunctionMap::iterator fit_it = fitting_functions.find(user_predefined_alpha_fit);
        if (fit_it != fitting_functions.end()) {
            if (!silence){std::cout << "Found the predefined fit for ALPHA." << std::endl;}
            class_alpha_fit = {fit_it->second, user_predefined_alpha_num_coeffs};
        } 
        else {throw std::range_error("Predefined ALPHA fit unknown.");}
    }

    if (full_alpha_fit_override)
    {
        if(alpha_override_num_coeffs){class_alpha_fit.second = alpha_num_coeffs;}
        if(alpha_override_scale_temp){std::get<0>(class_alpha_fit.first.second) = alpha_scale_temp;}
        if(alpha_override_temp_scale_min){std::get<1>(class_alpha_fit.first.second) = alpha_temp_scale_min;}
        if(alpha_override_temp_scale_max){std::get<2>(class_alpha_fit.first.second) = alpha_temp_scale_max;}
        if(alpha_override_fit_function){
            BasisFunctionMap::iterator basis_it = basis_functions.find(alpha_basis_function);
            if (basis_it != basis_functions.end()){std::get<3>(class_alpha_fit.first.second) = basis_it->second;}
            else {throw std::range_error("Unknown ALPHA fitting function.");}
        }
    }
}

void OTFData::generate_coefficients(){
    __generate_A_matrices__();
    __solve__();
}

void OTFData::write_coefficients(){
    H5::FileCreatPropList fcpl;
    H5::FileAccPropList fapl;
    H5::H5File file(otf_output_file, H5F_ACC_TRUNC, fcpl, fapl);

    writeHDF5Int(file, za, "ZA");
    writeHDF5Int(file, mat, "MAT");
    writeHDF5Double(file, a0, "A0");
    writeHDF5Double(file, e_max, "E_MAX");
    writeHDF5Double(file, m0, "M0");
    writeHDF5Double(file, free_xs, "FREE_XS");
    writeHDF5Double(file, bound_xs, "BOUND_XS");

    writeHDF5Double(file, temps.front(), "Minimum Temperature");
    writeHDF5Double(file, temps.back(), "Maximum Temperature");

    writeHDF5Bool(file, std::get<0>(class_xs_fit.first.second), "Scale XS temperatures");
    writeHDF5Double(file, std::get<1>(class_xs_fit.first.second), "XS Minimum Scaled Value");
    writeHDF5Double(file, std::get<2>(class_xs_fit.first.second), "XS Maximum Scaled Value");
    writeHDF5String(file, std::get<3>(class_xs_fit.first.second).first, "XS Fitting Function");
    
    writeHDF5Bool(file, std::get<0>(class_beta_fit.first.second), "Scale BETA temperatures");
    writeHDF5Double(file, std::get<1>(class_beta_fit.first.second), "BETA Minimum Scaled Value");
    writeHDF5Double(file, std::get<2>(class_beta_fit.first.second), "BETA Maximum Scaled Value");
    writeHDF5String(file, std::get<3>(class_beta_fit.first.second).first, "BETA Fitting Function");

    writeHDF5Bool(file, std::get<0>(class_alpha_fit.first.second), "Scale ALPHA temperatures");
    writeHDF5Double(file, std::get<1>(class_alpha_fit.first.second), "ALPHA Minimum Scaled Value");
    writeHDF5Double(file, std::get<2>(class_alpha_fit.first.second), "ALPHA Maximum Scaled Value");
    writeHDF5String(file, std::get<3>(class_alpha_fit.first.second).first, "ALPHA Fitting Function");

    writeHDF5DoubleVector(file, inc_energy_grid, "Incident Energy Grid");
    writeHDF5DoubleVector(file, beta_cdf_grid, "Beta CDF Grid");
    writeHDF5DoubleVector(file, beta_grid, "Beta Grid");
    writeHDF5DoubleVector(file, alpha_cdf_grid, "Alpha CDF Grid");

    __write_xs_Coeffs__(file, xs_coeffs, "XS_Coefficients");
    __write_fit_Coeffs__(file, beta_coeffs, "Beta Coefficients");
    __write_fit_Coeffs__(file, alpha_coeffs, "Alpha Coefficients");
}

void OTFData::__generate_A_matrices__(){
    if (std::get<0>(class_xs_fit.first.second)){xs_temps = scale_array(temps, std::get<1>(class_xs_fit.first.second), std::get<2>(class_xs_fit.first.second));}
    else {xs_temps = temps;}
    if (std::get<0>(class_beta_fit.first.second)){beta_temps = scale_array(temps, std::get<1>(class_beta_fit.first.second), std::get<2>(class_beta_fit.first.second));}
    else {beta_temps = temps;}
    if (std::get<0>(class_alpha_fit.first.second)){alpha_temps = scale_array(temps, std::get<1>(class_alpha_fit.first.second), std::get<2>(class_alpha_fit.first.second));}
    else {alpha_temps = temps;}
    xs_A.resize(temps.size(), class_xs_fit.second);
    beta_A.resize(temps.size(), class_beta_fit.second);
    alpha_A.resize(temps.size(), class_alpha_fit.second);
    __fill_A_matrices__();
}

void OTFData::__fill_A_matrices__(){
    if (!silence){
        std::cout << "Energy fitting function selected | " << class_xs_fit.first.first << " | Number Coefficients | " << class_xs_fit.second << std::endl;
        std::cout << "Beta fitting function selected | " << class_beta_fit.first.first << " | Number Coefficients | " << class_beta_fit.second << std::endl;
        std::cout << "Alpha fitting function selected | " << class_alpha_fit.first.first << " | Number Coefficients | " << class_alpha_fit.second << std::endl;
    }
    for (int i = 0; i<temps.size(); i++){
        Eigen::VectorXd evaled_xs_points = __eval_fit_func__(xs_temps[i], class_xs_fit.second, std::get<3>(class_xs_fit.first.second).second);
        xs_A(i, Eigen::placeholders::all) = evaled_xs_points;
        Eigen::VectorXd evaled_beta_points = __eval_fit_func__(beta_temps[i], class_beta_fit.second, std::get<3>(class_beta_fit.first.second).second);
        beta_A(i, Eigen::placeholders::all) = evaled_beta_points;
        Eigen::VectorXd evaled_alpha_points = __eval_fit_func__(alpha_temps[i], class_alpha_fit.second, std::get<3>(class_alpha_fit.first.second).second);
        alpha_A(i, Eigen::placeholders::all) = evaled_alpha_points;
    }
}

Eigen::VectorXd OTFData::__eval_fit_func__(double const & x, int const & number, FuncPointer func){
    Eigen::VectorXd eval(number);
    for (int i = 0; i<number; i++){
        eval(i) = func(x, i);
    }
    return eval;
}

void OTFData::__solve__(){
    // Currently just implements the normal equations.  From eye, this doesn't seem to cause numerical errors.
    Eigen::MatrixXd xs_A_T = xs_A.transpose();
    Eigen::MatrixXd beta_A_T = beta_A.transpose();
    Eigen::MatrixXd alpha_A_T = alpha_A.transpose();

    Eigen::LDLT<Eigen::MatrixXd> xs_ldlt = (xs_A_T * xs_A).ldlt();
    Eigen::LDLT<Eigen::MatrixXd> beta_ldlt = (beta_A_T * beta_A).ldlt();
    Eigen::LDLT<Eigen::MatrixXd> alpha_ldlt = (alpha_A_T * alpha_A).ldlt();

    // XS
    #pragma omp parallel for
    for (int i = 0; i<inc_energy_grid.size(); i++){
        xs_coeffs[i] = xs_ldlt.solve(xs_A_T * ii_xs[i]);
    }
    // BETA
    #pragma omp parallel for collapse(2)
    for (int i = 0; i<inc_energy_grid.size(); i++){
        for (int j = 0; j<beta_cdf_grid.size(); j++){
            beta_coeffs[i][j] = beta_ldlt.solve(beta_A_T * fit_beta_vals[i][j]);
        }
    }
    //ALPHA
    #pragma omp parallel for collapse(2)
    for (int i = 0; i<beta_grid.size(); i++){
        for (int j = 0; j<alpha_cdf_grid.size(); j++){
            alpha_coeffs[i][j] = alpha_ldlt.solve(alpha_A_T * fit_alpha_vals[i][j]);
        }
    }
}

template<typename T> void OTFData::__check__(T const & val_1, T const & val_2, std::string const item_name){
    std::string error_message = item_name + " are not equal.  Terminating.";
    if (val_1 != val_2){
        throw std::runtime_error(error_message);
    }
}