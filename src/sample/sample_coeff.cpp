#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <omp.h>
#include <chrono>

#include "H5Cpp.h"

#include "sample_coeff.hpp"

#include "runtime_variables.hpp"
#include "constants.hpp"
#include "hdf5_file.hpp"
#include "interpolation.hpp"
#include "scale_basis.hpp"

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
    set_eval_function__(xs_eval_func, xs_basis_function_string);

    readHDF5Bool(file, "Scale BETA temperatures", beta_scale_temperatures);
    readHDF5Double(file, "BETA Minimum Scaled Value", beta_scale_minimum);
    readHDF5Double(file, "BETA Maximum Scaled Value", beta_scale_maximum);
    readHDF5String(file, "BETA Fitting Function", beta_basis_function_string);
    set_eval_function__(beta_eval_func, beta_basis_function_string);

    readHDF5Bool(file, "Scale ALPHA temperatures", alpha_scale_temperatures);
    readHDF5Double(file, "ALPHA Minimum Scaled Value", alpha_scale_minimum);
    readHDF5Double(file, "ALPHA Maximum Scaled Value", alpha_scale_maximum);
    readHDF5String(file, "ALPHA Fitting Function", alpha_basis_function_string);
    set_eval_function__(alpha_eval_func, alpha_basis_function_string);

    readHDF5DoubleVector(file, "Incident Energy Grid", inc_ener_grid);
    readHDF5DoubleVector(file, "Beta CDF Grid", beta_cdf_grid);
    readHDF5DoubleVector(file, "Beta Grid", beta_grid);
    readHDF5DoubleVector(file, "Alpha CDF Grid", alpha_cdf_grid);

    readHDF5DoubleVector(file, "XS_Coefficients", ii_xs_coeffs);
    num_xs_coeff = ii_xs_coeffs.size()/inc_ener_grid.size();
    readHDF5DoubleVector(file, "Beta Coefficients", beta_coeffs);
    num_beta_coeffs = beta_coeffs.size()/(inc_ener_grid.size()*beta_cdf_grid.size());
    readHDF5DoubleVector(file, "Alpha Coefficients", alpha_coeffs);
    num_alpha_coeffs = alpha_coeffs.size()/(beta_grid.size()*alpha_cdf_grid.size());
}

void CoeffFile::set_eval_function__(EvaluationFunction & eval_func, std::string const &basis_func_string)
{
    auto it = OptimalEvaluationsMap.find(basis_func_string);
    if (it != OptimalEvaluationsMap.end()) {eval_func = it->second;} 
    else {throw std::out_of_range("Unknown basis function used for coefficient fitting.");}
}

std::pair<double, double> CoeffFile::return_alpha_extrema__(const double &inc_ener, const double &beta){
    double t1 = sqrt(inc_ener);
    double t2 = a0*boltz*sample_temperature;
    double t3 = sqrt(abs(inc_ener + beta*boltz*sample_temperature));
    double t4 = t1 - t3;
    double t5 = t1 + t3;
    return std::pair<double, double>((t4*t4)/t2,(t5*t5)/t2);
}

std::pair<double, double> CoeffFile::single_sample(const double &inc_ener, const double &xi_1, const double &xi_2){
    return std::pair<double, double>();
}

void CoeffFile::all_sample(const double &inc_ener){
    #pragma omp parallel for
    for (int i = 0; i < sample_num_samples; ++i){
        std::pair<double, double> results = single_sample(inc_ener, xi_1[i], xi_2[i]);
        sampled_secondary_energies[i] = results.first;
        sampled_scattering_cosines[i] = results.second;
    }
}


void sample_coeff(){
    CoeffFile data(sample_input_file);

    std::cout << data.num_xs_coeff << "  " << data.num_beta_coeffs << "  " << data.num_alpha_coeffs << std::endl;

    // Reserve sampling space
    data.sampled_secondary_energies.resize(sample_num_samples);
    data.sampled_scattering_cosines.resize(sample_num_samples);

    // Create Random number vectors
    data.xi_1.resize(sample_num_samples);
    data.xi_2.resize(sample_num_samples);
    std::mt19937 gen(sample_seed); // Mersenne Twister engine
    std::uniform_real_distribution<> dis(0.0, 1.0); // Uniform distribution [0, 1]
    for (int i = 0; i < sample_num_samples; ++i) {
        data.xi_1[i] = dis(gen);
        data.xi_2[i] = dis(gen);
    }

    // Do the sampling
    auto sampling_start = std::chrono::high_resolution_clock::now();
    data.all_sample(sample_incident_energy);
    auto sampling_end = std::chrono::high_resolution_clock::now();
    auto sampling_duration = std::chrono::duration_cast<std::chrono::milliseconds>(sampling_end-sampling_start);
    data.time_to_sample_ms = sampling_duration.count();
    if (!silence){
        std::cout << "Time to sample | milliseconds " << data.time_to_sample_ms << std::endl;
    }
}