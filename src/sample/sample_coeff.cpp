#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <omp.h>
#include <chrono>

#include "H5Cpp.h"

#include "sample_coeff.hpp"

#include "sample_search.hpp"
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
    readHDF5Double(file, "Minimum Temperature", minimum_temperature);
    readHDF5Double(file, "Maximum Temperature", maximum_temperature);
    
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
    num_xs_coeffs = ii_xs_coeffs.size()/inc_ener_grid.size();
    readHDF5DoubleVector(file, "Beta Coefficients", beta_coeffs);
    num_beta_coeffs = beta_coeffs.size()/(inc_ener_grid.size()*beta_cdf_grid.size());
    readHDF5DoubleVector(file, "Alpha Coefficients", alpha_coeffs);
    num_alpha_coeffs = alpha_coeffs.size()/(beta_grid.size()*alpha_cdf_grid.size());
}

void CoeffFile::set_eval_function__(EvaluationFunction &eval_func, std::string const &basis_func_string)
{
    auto it = evaluation_functions.find(basis_func_string);
    if (it != evaluation_functions.end()) {eval_func = it->second;} 
    else {throw std::out_of_range("Unknown basis function.");}
}

std::pair<double, double> CoeffFile::return_alpha_extrema__(const double & temp, const double &inc_ener, const double &beta){
    double t1 = sqrt(inc_ener);
    double t2 = a0*boltz*temp;
    double t3 = sqrt(abs(inc_ener + beta*boltz*temp));
    double t4 = t1 - t3;
    double t5 = t1 + t3;
    return std::pair<double, double>((t4*t4)/t2,(t5*t5)/t2);
}

std::pair<double, double> CoeffFile::single_sample(const double & temp, const double & inc_ener, const double & xi_1, const double & xi_2){
    double sampled_beta = sample_beta__(temp, inc_ener, xi_1);
    double sampled_scattering_energy = calculate_secondary_energy__(temp, inc_ener, sampled_beta);
    double sampled_alpha = sample_alpha__(temp, inc_ener, sampled_beta, xi_2);
    double sampled_scattering_cosine = calculate_scattering_cosine__(temp, inc_ener, sampled_scattering_energy, sampled_alpha);
    return std::pair<double, double>(sampled_scattering_energy, sampled_scattering_cosine);
}

double CoeffFile::sample_beta__(const double &temp, const double &inc_ener, const double &xi)
{
    double eval_point;
    if(beta_scale_temperatures){
        eval_point = scale_value(temp, minimum_temperature, maximum_temperature, beta_scale_minimum, beta_scale_maximum);
    }
    else{
        eval_point = temp;
    }
    std::vector<double> evaled_basis_points = beta_eval_func.eval_basis_func_pointer(eval_point, num_beta_coeffs - 1);
    auto [lo_inc_ener_ind, hi_inc_ener_ind] = findSampleInterpolationIndices(inc_ener_grid.begin(), inc_ener_grid.end() - 1, inc_ener);
    auto [lo_beta_cdf_ind, hi_beta_cdf_ind] = findSampleInterpolationIndices(beta_cdf_grid.begin(), beta_cdf_grid.end() - 1, xi);
    std::vector<double>::const_iterator f11_i = beta_coeffs.begin() + num_beta_coeffs*(lo_inc_ener_ind*beta_cdf_grid.size() + lo_beta_cdf_ind);
    std::vector<double>::const_iterator f12_i = beta_coeffs.begin() + num_beta_coeffs*(lo_inc_ener_ind*beta_cdf_grid.size() + hi_beta_cdf_ind);
    std::vector<double>::const_iterator f21_i = beta_coeffs.begin() + num_beta_coeffs*(hi_inc_ener_ind*beta_cdf_grid.size() + lo_beta_cdf_ind);
    std::vector<double>::const_iterator f22_i = beta_coeffs.begin() + num_beta_coeffs*(hi_inc_ener_ind*beta_cdf_grid.size() + hi_beta_cdf_ind);
    return bi_interp(inc_ener_grid[lo_inc_ener_ind], // x1
                     inc_ener_grid[hi_inc_ener_ind], // x2
                     beta_cdf_grid[lo_beta_cdf_ind], // y1
                     beta_cdf_grid[hi_beta_cdf_ind], // y2
                     std::inner_product(f11_i, f11_i + num_beta_coeffs, evaled_basis_points.begin(), 0.0), //f11
                     std::inner_product(f12_i, f12_i + num_beta_coeffs, evaled_basis_points.begin(), 0.0), //f12
                     std::inner_product(f21_i, f21_i + num_beta_coeffs, evaled_basis_points.begin(), 0.0), //f21
                     std::inner_product(f22_i, f22_i + num_beta_coeffs, evaled_basis_points.begin(), 0.0), //f22
                     inc_ener, // x
                     xi); // y
}

double CoeffFile::calculate_secondary_energy__(const double &temp, const double &inc_ener, const double &beta)
{
    return inc_ener + beta*boltz*temp;
}

double CoeffFile::sample_alpha__(const double &temp, const double &inc_ener, const double &beta, const double &xi)
{
    double eval_point;
    if(alpha_scale_temperatures){
        eval_point = scale_value(temp, minimum_temperature, maximum_temperature, alpha_scale_minimum, alpha_scale_maximum);
    }
    else{
        eval_point = temp;
    }
    std::vector<double> evaled_alpha_points = alpha_eval_func.eval_basis_func_pointer(eval_point, num_alpha_coeffs - 1);
    std::pair<double, double> alpha_extrema = return_alpha_extrema__(temp, inc_ener, beta);
    
    // Unscale and abs the beta to search the alpha storage beta grid
    double grid_beta = abs(beta * temp/ref_temp_k);

    auto [lo_beta_ind, hi_beta_ind] = findSampleInterpolationIndices(beta_grid.begin(), beta_grid.end()-1, grid_beta);

    double l_alpha = sample_bounding_alpha__(temp, lo_beta_ind, alpha_extrema, xi, evaled_alpha_points);
    double u_alpha = sample_bounding_alpha__(temp, hi_beta_ind, alpha_extrema, xi, evaled_alpha_points);
    return ENDF_interp(beta_grid[lo_beta_ind],
                       beta_grid[hi_beta_ind],
                       l_alpha,
                       u_alpha,
                       grid_beta); 
}

double CoeffFile::sample_bounding_alpha__(const double &temp, const int &beta_ind, const std::pair<double, double> &alpha_extrema, const double &xi, const std::vector<double> &evaled_basis_points)
{
    std::vector<double>::const_iterator alpha_start = alpha_coeffs.begin() + beta_ind*alpha_cdf_grid.size()*num_alpha_coeffs;
    std::vector<double>::const_iterator alpha_end = alpha_start + alpha_cdf_grid.size()*num_alpha_coeffs;

    auto [l_amin_ind, u_amin_ind] = findSampleCoeffInterpolationIndices(alpha_start, alpha_end - num_alpha_coeffs, alpha_extrema.first, evaled_basis_points);
    std::vector<double>::const_iterator x1_i = alpha_coeffs.begin() + num_alpha_coeffs*(beta_ind*alpha_cdf_grid.size() + l_amin_ind);
    std::vector<double>::const_iterator x2_i = alpha_coeffs.begin() + num_alpha_coeffs*(beta_ind*alpha_cdf_grid.size() + u_amin_ind);
    double x1 = std::inner_product(x1_i, x1_i + num_alpha_coeffs, evaled_basis_points.begin(), 0.0);
    double x2 = std::inner_product(x2_i, x2_i + num_alpha_coeffs, evaled_basis_points.begin(), 0.0);
    double u_amin_cdf = ENDF_interp(x1, x2, alpha_cdf_grid[l_amin_ind], alpha_cdf_grid[u_amin_ind], alpha_extrema.first);

    auto [l_amax_ind, u_amax_ind] = findSampleCoeffInterpolationIndices(alpha_start, alpha_end - num_alpha_coeffs, alpha_extrema.second, evaled_basis_points);
    x1_i = alpha_coeffs.begin() + num_alpha_coeffs*(beta_ind*alpha_cdf_grid.size() + l_amax_ind);
    x2_i = alpha_coeffs.begin() + num_alpha_coeffs*(beta_ind*alpha_cdf_grid.size() + u_amax_ind);
    x1 = std::inner_product(x1_i , x1_i + num_alpha_coeffs, evaled_basis_points.begin(), 0.0);
    x2 = std::inner_product(x2_i , x2_i + num_alpha_coeffs, evaled_basis_points.begin(), 0.0);
    double u_amax_cdf = ENDF_interp(x1, x2, alpha_cdf_grid[l_amax_ind], alpha_cdf_grid[u_amax_ind], alpha_extrema.second);

    double xi_prime = scale_value(xi, 0, 1, u_amin_cdf, u_amax_cdf);
    auto [l_alpha_cdf_ind, u_alpha_cdf_ind] = findInterpolationIndexes(alpha_cdf_grid.begin(), alpha_cdf_grid.end(), xi_prime);
    x1_i = alpha_coeffs.begin() + num_alpha_coeffs*(beta_ind*alpha_cdf_grid.size() + l_alpha_cdf_ind);
    x2_i = alpha_coeffs.begin() + num_alpha_coeffs*(beta_ind*alpha_cdf_grid.size() + u_alpha_cdf_ind);
    x1 = std::inner_product(x1_i, x1_i + num_alpha_coeffs, evaled_basis_points.begin(), 0.0);
    x2 = std::inner_product(x2_i, x2_i + num_alpha_coeffs, evaled_basis_points.begin(), 0.0);    
    double alpha = ENDF_interp(alpha_cdf_grid[l_alpha_cdf_ind], alpha_cdf_grid[u_alpha_cdf_ind], x1, x2, xi_prime);
    return alpha;
}

double CoeffFile::calculate_scattering_cosine__(const double &temp, const double &inc_ener, const double &sec_ener, const double &alpha)
{
    return ((inc_ener + sec_ener) - alpha*a0*boltz*temp)/(2*sqrt(inc_ener*sec_ener));
}

void CoeffFile::all_sample(const double &inc_ener){
    #pragma omp parallel for
    for (int i = 0; i < sample_num_samples; ++i){
        std::pair<double, double> results = single_sample(sample_temperature, inc_ener, xi_1[i], xi_2[i]);
        sampled_secondary_energies[i] = results.first;
        sampled_scattering_cosines[i] = results.second;
    }
}

void CoeffFile::write_results(){
    H5::FileCreatPropList fcpl;
    H5::FileAccPropList fapl;
    H5::H5File file(sample_output_file, H5F_ACC_TRUNC, fcpl, fapl);

    writeHDF5Int(file, za, "ZA");
    writeHDF5Int(file, mat, "MAT");
    writeHDF5Double(file, a0, "A0");
    writeHDF5Double(file, e_max, "E_MAX");
    writeHDF5Double(file, m0, "M0");
    writeHDF5Double(file, free_xs, "FREE_XS");
    writeHDF5Double(file, bound_xs, "BOUND_XS");

    writeHDF5Int(file, xi_1.size(), "Number of Samples");
    writeHDF5Double(file, sample_temperature, "Sampling Temperature");
    writeHDF5Double(file, time_to_sample_ms, "Sampling Time [ms]");

    if (!sample_only_timing_results){
        writeHDF5DoubleVector(file, sampled_secondary_energies, "Sampled Energies");
        writeHDF5DoubleVector(file, sampled_scattering_cosines, "Sampled Cosines");
    }

    file.close();
}

void sample_coeff(){
    CoeffFile data(sample_input_file);

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

    // Write the sampling results
    auto file_write_start = std::chrono::high_resolution_clock::now();
    data.write_results();
    auto file_write_end = std::chrono::high_resolution_clock::now();
    auto file_write_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_write_end-file_write_start);
    if (!silence){
        std::cout << "Time to write the coefficient sampling results coefficients | milliseconds " << file_write_duration.count() << std::endl;
    }
}