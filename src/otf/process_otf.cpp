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
    for (size_t i; i<beta_grid.size(); i++){
        for (size_t j; j<alpha_cdf_grid.size(); j++){
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
    load_fit_settings__();
}

void OTFData::load_fit_settings__(){
    MatPredefinedFitMap::iterator default_fits_it = material_predefined_fits.find(mat);
    if (default_fits_it != material_predefined_fits.end()) {
        if (!silence){std::cout << "Found the material fit settings." << std::endl;}
        load_material_fit_settings__(default_fits_it);
    } 
    else {
        if (!silence){std::cout << "Material does not have predefined settings.  Loading the default fit.";}
        load_default_fit_settings__();
    }
    if (!silence){std::cout << "Overriding fit settings if desired." << std::endl;}
    override_fit_settings__();
}

void OTFData::load_material_fit_settings__(MatPredefinedFitMap::iterator mat_it){
    MatPredefinedFits all_fits = mat_it->second;
    PredefinedFit xs_fit = std::get<0>(all_fits);
    PredefinedFit beta_fit = std::get<1>(all_fits);
    PredefinedFit alpha_fit = std::get<2>(all_fits);

    PredefinedFitSettings xs_fit_settings = xs_fit.first;
    class_xs_num_coeffs = xs_fit.second;
    class_xs_scale_temp = std::get<0>(xs_fit_settings.second);
    class_xs_temp_scale_min = std::get<1>(xs_fit_settings.second);
    class_xs_temp_scale_max = std::get<2>(xs_fit_settings.second);
    class_xs_fit_function = std::get<3>(xs_fit_settings.second);

    PredefinedFitSettings beta_fit_settings = beta_fit.first;
    class_beta_num_coeffs = beta_fit.second;
    class_beta_scale_temp = std::get<0>(beta_fit_settings.second);
    class_beta_temp_scale_min = std::get<1>(beta_fit_settings.second);
    class_beta_temp_scale_max = std::get<2>(beta_fit_settings.second);
    class_beta_fit_function = std::get<3>(beta_fit_settings.second);

    PredefinedFitSettings alpha_fit_settings = alpha_fit.first;
    class_alpha_num_coeffs = alpha_fit.second;
    class_alpha_scale_temp = std::get<0>(alpha_fit_settings.second);
    class_alpha_temp_scale_min = std::get<1>(alpha_fit_settings.second);
    class_alpha_temp_scale_max = std::get<2>(alpha_fit_settings.second);
    class_alpha_fit_function = std::get<3>(alpha_fit_settings.second);
}

void OTFData::load_default_fit_settings__(){
    FitSettings fitset = default_fit.first.second;
    int num = default_fit.second;
    bool scale = std::get<0>(fitset);
    double min = std::get<1>(fitset);
    double max = std::get<2>(fitset);
    FitFunction func = std::get<3>(fitset);

    class_xs_num_coeffs = num;
    class_xs_scale_temp = scale;
    class_xs_temp_scale_min = min;
    class_xs_temp_scale_max = max;
    class_xs_fit_function = func;

    class_beta_num_coeffs = num;
    class_beta_scale_temp = scale;
    class_beta_temp_scale_min = min;
    class_beta_temp_scale_max = max;
    class_beta_fit_function = func;

    class_alpha_num_coeffs = num;
    class_alpha_scale_temp = scale;
    class_alpha_temp_scale_min = min;
    class_alpha_temp_scale_max = max;
    class_alpha_fit_function = func;
}

void OTFData::override_fit_settings__(){
    if (basic_xs_fit_override){
        PredefinedFitSettingsMap::iterator fit_it = predefined_fit_settings.find(user_predefined_xs_fit);
        if (fit_it != predefined_fit_settings.end()) {
            if (!silence){std::cout << "Found the predefined fit for XS." << std::endl;}
            PredefinedFitSettings fit = fit_it->second;
            FitSettings fit_set = fit.second;
            class_xs_scale_temp = std::get<0>(fit_set);
            class_xs_temp_scale_min = std::get<1>(fit_set);
            class_xs_temp_scale_max = std::get<2>(fit_set);
            class_xs_fit_function = std::get<3>(fit_set);
            class_xs_num_coeffs = user_predefined_xs_num_coeffs;
        } 
        else {throw std::range_error("Predefined XS fit unknown.");}
    }

    if (full_xs_fit_override)
    {
        if(xs_override_num_coeffs){class_xs_num_coeffs = xs_num_coeffs;}
        if(xs_override_scale_temp){class_xs_scale_temp = xs_scale_temp;}
        if(xs_override_temp_scale_min){class_xs_temp_scale_min = xs_temp_scale_min;}
        if(xs_override_temp_scale_max){class_xs_temp_scale_max = xs_temp_scale_max;}
        if(xs_override_fit_function){
            MapFittingFunctions::iterator fit_func_it = fitting_functions.find(xs_fit_function);
            if (fit_func_it != fitting_functions.end()){class_xs_fit_function = fit_func_it->second;}
            else {throw std::range_error("Unknown XS fitting function.");}
        }
    }
    
    if (basic_beta_fit_override){
        PredefinedFitSettingsMap::iterator fit_it = predefined_fit_settings.find(user_predefined_beta_fit);
        if (fit_it != predefined_fit_settings.end()) {
            if (!silence){std::cout << "Found the predefined fit for BETA." << std::endl;}
            PredefinedFitSettings fit = fit_it->second;
            FitSettings fit_set = fit.second;
            class_beta_scale_temp = std::get<0>(fit_set);
            class_beta_temp_scale_min = std::get<1>(fit_set);
            class_beta_temp_scale_max = std::get<2>(fit_set);
            class_beta_fit_function = std::get<3>(fit_set);
            class_beta_num_coeffs = user_predefined_beta_num_coeffs;
        } 
        else {throw std::range_error("Predefined BETA fit unknown.");}
    }

    if (full_beta_fit_override){
        if(beta_override_num_coeffs){class_beta_num_coeffs = beta_num_coeffs;}
        if(beta_override_scale_temp){class_beta_scale_temp = beta_scale_temp;}
        if(beta_override_temp_scale_min){class_beta_temp_scale_min = beta_temp_scale_min;}
        if(beta_override_temp_scale_max){class_beta_temp_scale_max = beta_temp_scale_max;}
        if(beta_override_fit_function){        
            MapFittingFunctions::iterator fit_func_it = fitting_functions.find(beta_fit_function);
            if (fit_func_it != fitting_functions.end()){class_beta_fit_function = fit_func_it->second;}
            else {throw std::range_error("Unknown BETA fitting function.");}
        }
    }
    
    if (basic_alpha_fit_override){
        PredefinedFitSettingsMap::iterator fit_it = predefined_fit_settings.find(user_predefined_alpha_fit);
        if (fit_it != predefined_fit_settings.end()) {
            if (!silence){std::cout << "Found the predefined fit for ALPHA." << std::endl;}
            PredefinedFitSettings fit = fit_it->second;
            FitSettings fit_set = fit.second;
            class_alpha_scale_temp = std::get<0>(fit_set);
            class_alpha_temp_scale_min = std::get<1>(fit_set);
            class_alpha_temp_scale_max = std::get<2>(fit_set);
            class_alpha_fit_function = std::get<3>(fit_set);
            class_alpha_num_coeffs = user_predefined_alpha_num_coeffs;
        } 
        else {throw std::range_error("Predefined ALPHA fit unknown.");}
    }

    if (full_alpha_fit_override){
        if(alpha_override_num_coeffs){class_alpha_num_coeffs = alpha_num_coeffs;}
        if(alpha_override_scale_temp){class_alpha_scale_temp = alpha_scale_temp;}
        if(alpha_override_temp_scale_min){class_alpha_temp_scale_min = alpha_temp_scale_min;}
        if(alpha_override_temp_scale_max){class_alpha_temp_scale_max = alpha_temp_scale_max;}
        if(alpha_override_fit_function){        
            MapFittingFunctions::iterator fit_func_it = fitting_functions.find(alpha_fit_function);
            if (fit_func_it != fitting_functions.end()){class_alpha_fit_function = fit_func_it->second;}
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

    writeHDF5Bool(file, class_xs_scale_temp, "Scale XS temperatures");
    writeHDF5Double(file, class_xs_temp_scale_min, "XS Minimum Scaled Value");
    writeHDF5Double(file, class_xs_temp_scale_max, "XS Maximum Scaled Value");
    writeHDF5String(file, class_xs_fit_function.first, "XS Fitting Function");
    
    writeHDF5Bool(file, class_beta_scale_temp, "Scale Beta temperatures");
    writeHDF5Double(file, class_beta_temp_scale_min, "Beta Minimum Scaled Value");
    writeHDF5Double(file, class_beta_temp_scale_max, "Beta Maximum Scaled Value");
    writeHDF5String(file, class_beta_fit_function.first, "Beta Fitting Function");

    writeHDF5Bool(file, class_alpha_scale_temp, "Scale Alpha temperatures");
    writeHDF5Double(file, class_alpha_temp_scale_min, "Alpha Minimum Scaled Value");
    writeHDF5Double(file, class_alpha_temp_scale_max, "Alpha Maximum Scaled Value");
    writeHDF5String(file, class_alpha_fit_function.first, "Alpha Fitting Function");

    writeHDF5DoubleVector(file, inc_energy_grid, "Incident Energy Grid");
    writeHDF5DoubleVector(file, beta_cdf_grid, "Beta CDF Grid");
    writeHDF5DoubleVector(file, beta_grid, "Beta Grid");
    writeHDF5DoubleVector(file, alpha_cdf_grid, "Alpha CDF Grid");

    __write_xs_Coeffs__(file, xs_coeffs, "XS_Coefficients");
    __write_fit_Coeffs__(file, beta_coeffs, "Beta Coefficients");
    __write_fit_Coeffs__(file, alpha_coeffs, "Alpha Coefficients");
}

void OTFData::__generate_A_matrices__(){
    if (class_xs_scale_temp){xs_temps = scale_array(temps, class_xs_temp_scale_min, class_xs_temp_scale_max);}
    else {xs_temps = temps;}
    if (class_beta_scale_temp){beta_temps = scale_array(temps, class_beta_temp_scale_min, class_beta_temp_scale_max);}
    else {beta_temps = temps;}
    if (class_alpha_scale_temp){alpha_temps = scale_array(temps, class_alpha_temp_scale_min, class_alpha_temp_scale_max);}
    else {alpha_temps = temps;}
    xs_A.resize(temps.size(), class_xs_num_coeffs);
    beta_A.resize(temps.size(), class_beta_num_coeffs);
    alpha_A.resize(temps.size(), class_alpha_num_coeffs);
    __fill_A_matrices__();
}

void OTFData::__fill_A_matrices__(){
    if (!silence){
        std::cout << "Energy fitting function selected | " << class_xs_fit_function.first << std::endl;
        std::cout << "Beta fitting function selected | " << class_beta_fit_function.first << std::endl;
        std::cout << "Alpha fitting function selected | " << class_alpha_fit_function.first << std::endl;
    }
    for (int i = 0; i<temps.size(); i++){
        Eigen::VectorXd evaled_xs_points = __eval_fit_func__(xs_temps[i], class_xs_num_coeffs, class_xs_fit_function.second);
        xs_A(i, Eigen::placeholders::all) = evaled_xs_points;
        Eigen::VectorXd evaled_beta_points = __eval_fit_func__(beta_temps[i], class_beta_num_coeffs, class_beta_fit_function.second);
        beta_A(i, Eigen::placeholders::all) = evaled_beta_points;
        Eigen::VectorXd evaled_alpha_points = __eval_fit_func__(alpha_temps[i], class_alpha_num_coeffs, class_alpha_fit_function.second);
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
    // XS
    for (int i = 0; i<inc_energy_grid.size(); i++){
        // // SVD
        // xs_coeffs[i] = xs_A.template bdcSvd<Eigen::ComputeThinU | Eigen::ComputeThinV>().solve(ii_xs[i]);
        // // Full pivot QR
        // xs_coeffs[i] = xs_A.fullPivHouseholderQr().solve(ii_xs[i]);
        // // Normal Equations
        xs_coeffs[i] = (xs_A.transpose() * xs_A).ldlt().solve(xs_A.transpose() * ii_xs[i]);
    }
    // BETA
    for (int i = 0; i<inc_energy_grid.size(); i++){
        for (int j = 0; j<beta_cdf_grid.size(); j++){
            // // SVD
            // beta_coeffs[i][j] = beta_A.template bdcSvd<Eigen::ComputeThinU | Eigen::ComputeThinV>().solve(fit_beta_vals[i][j]);
            // // Full pivot QR
            // beta_coeffs[i][j] = beta_A.fullPivHouseholderQr().solve(fit_beta_vals[i][j]);
            // // Normal Equations
            beta_coeffs[i][j] = (beta_A.transpose() * beta_A).ldlt().solve(beta_A.transpose() * fit_beta_vals[i][j]);
        }
    }
    //ALPHA
    for (int i = 0; i<beta_grid.size(); i++){
        for (int j = 0; j<alpha_cdf_grid.size(); j++){
            // // SVD
            // alpha_coeffs[i][j] = alpha_A.template bdcSvd<Eigen::ComputeThinU | Eigen::ComputeThinV>().solve(fit_alpha_vals[i][j]);
            // // Full pivot QR
            // alpha_coeffs[i][j] = alpha_A.fullPivHouseholderQr().solve(fit_alpha_vals[i][j]);
            // // Normal Equations
            alpha_coeffs[i][j] = (alpha_A.transpose() * alpha_A).ldlt().solve(alpha_A.transpose() * fit_alpha_vals[i][j]);
        }
    }
}

template<typename T> void OTFData::__check__(T const & val_1, T const & val_2, std::string const item_name){
    std::string error_message = item_name + " are not equal.  Terminating.";
    if (val_1 != val_2){
        throw std::runtime_error(error_message);
    }
}