#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <omp.h>
#include <chrono>

#include "sample_cdf.hpp"

#include "sample_search.hpp"
#include "runtime_variables.hpp"
#include "constants.hpp"
#include "interpolation.hpp"
#include "scale_basis.hpp"

CDFFile::CDFFile(std::string const & file_path){
    // H5::H5File file(file_path, H5F_ACC_RDONLY);

    // readHDF5Int(file, "ZA", za);
    // readHDF5Int(file, "MAT", mat);
    // readHDF5Double(file, "Temp", temp);
    // readHDF5Double(file, "T_EFF", t_eff);
    // readHDF5Double(file, "TEMP_RATIO", temp_ratio);
    // readHDF5Double(file, "A0", a0);
    // readHDF5Double(file, "E_MAX", e_max);
    // readHDF5Double(file, "M0", m0);
    // readHDF5Double(file, "FREE_XS", free_xs);
    // readHDF5Double(file, "BOUND_XS", bound_xs);
    // readHDF5DoubleVector(file, "Incident Energy Grid", inc_ener_grid);
    // readHDF5DoubleVector(file, "Incoherent Inelastic XS", ii_xs);
    // readHDF5DoubleVector(file, "Beta CDF Grid", beta_cdf_grid);
    // readHDF5DoubleVector(file, "Fit Betas", fit_betas);
    // readHDF5DoubleVector(file, "Beta Grid", beta_grid);
    // readHDF5DoubleVector(file, "Alpha CDF Grid", alpha_cdf_grid);
    // readHDF5DoubleVector(file, "Fit Alphas", fit_alphas);
}

std::pair<double, double> CDFFile::return_alpha_extrema__(const double &inc_ener, const double &beta){
    double t1 = sqrt(inc_ener);
    double t2 = a0*boltz*temp;
    double t3 = sqrt(abs(inc_ener + beta*boltz*temp));
    double t4 = t1 - t3;
    double t5 = t1 + t3;
    return std::pair<double, double>((t4*t4)/t2,(t5*t5)/t2);
}

std::pair<double, double> CDFFile::single_sample(const double & inc_ener, const double & xi_1, const double & xi_2){
    double sampled_beta = sample_beta__(inc_ener, xi_1);
    double sampled_scattering_energy = calculate_secondary_energy__(inc_ener, sampled_beta);
    double sampled_alpha = sample_alpha__(inc_ener, sampled_beta, xi_2);
    double sampled_scattering_cosine = calculate_scattering_cosine__(inc_ener, sampled_scattering_energy, sampled_alpha);
    return std::pair<double, double>(sampled_scattering_energy, sampled_scattering_cosine);
}

double CDFFile::sample_beta__(const double &inc_ener, const double &xi)
{
    auto [lo_inc_ener_ind, hi_inc_ener_ind] = findSampleInterpolationIndices(inc_ener_grid.begin(), inc_ener_grid.end()-1, inc_ener);
    auto [lo_beta_cdf_ind, hi_beta_cdf_ind] = findSampleInterpolationIndices(beta_cdf_grid.begin(), beta_cdf_grid.end()-1, xi);
    return bi_interp(inc_ener_grid[lo_inc_ener_ind], // x1
                     inc_ener_grid[hi_inc_ener_ind], // x2
                     beta_cdf_grid[lo_beta_cdf_ind], // y1
                     beta_cdf_grid[hi_beta_cdf_ind], // y2
                     fit_betas[lo_inc_ener_ind*beta_cdf_grid.size() + lo_beta_cdf_ind], //f11
                     fit_betas[lo_inc_ener_ind*beta_cdf_grid.size() + hi_beta_cdf_ind], //f12
                     fit_betas[hi_inc_ener_ind*beta_cdf_grid.size() + lo_beta_cdf_ind], //f21
                     fit_betas[hi_inc_ener_ind*beta_cdf_grid.size() + hi_beta_cdf_ind], //f22
                     inc_ener, // x
                     xi); // y
}

double CDFFile::calculate_secondary_energy__(const double &inc_ener, const double &beta)
{
    return inc_ener + beta*boltz*temp;
}

double CDFFile::sample_alpha__(const double &inc_ener, const double &beta, const double &xi)
{
    std::pair<double, double> alpha_extrema = return_alpha_extrema__(inc_ener, beta);
    
    // Unscale and abs the beta to search the alpha storage beta grid
    double grid_beta = abs(beta * temp/ref_temp_k);

    auto [lo_beta_ind, hi_beta_ind] = findSampleInterpolationIndices(beta_grid.begin(), beta_grid.end()-1, grid_beta);

    double l_alpha = sample_bounding_alpha__(lo_beta_ind, alpha_extrema, xi);
    double u_alpha = sample_bounding_alpha__(hi_beta_ind, alpha_extrema, xi);
    return ENDF_interp(beta_grid[lo_beta_ind],
                       beta_grid[hi_beta_ind],
                       l_alpha,
                       u_alpha,
                       grid_beta);   
}

double CDFFile::sample_bounding_alpha__(const int &beta_ind, const std::pair<double, double> &alpha_extrema, const double &xi)
{
    std::vector<double>::iterator alpha_start = fit_alphas.begin() + beta_ind*alpha_cdf_grid.size();
    int alpha_start_ind = std::distance(fit_alphas.begin(), alpha_start);
    std::vector<double>::iterator alpha_end = alpha_start + alpha_cdf_grid.size();
    auto [l_amin_ind, u_amin_ind] = findSampleInterpolationIndices(alpha_start, alpha_end - 1, alpha_extrema.first);
    double amin_cdf = ENDF_interp(fit_alphas[alpha_start_ind+l_amin_ind],
                                    fit_alphas[alpha_start_ind+u_amin_ind],
                                    alpha_cdf_grid[l_amin_ind],
                                    alpha_cdf_grid[u_amin_ind],
                                    alpha_extrema.first);
    auto [l_amax_ind, u_amax_ind] = findSampleInterpolationIndices(alpha_start, alpha_end - 1, alpha_extrema.second);
    double amax_cdf = ENDF_interp(fit_alphas[alpha_start_ind+l_amax_ind],
                                    fit_alphas[alpha_start_ind+u_amax_ind],
                                    alpha_cdf_grid[l_amax_ind],
                                    alpha_cdf_grid[u_amax_ind],
                                    alpha_extrema.second);
    double xi_prime = scale_value(xi, 0, 1, amin_cdf, amax_cdf);
    auto [l_alpha_cdf_ind, u_alpha_cdf_ind] = findSampleInterpolationIndices(alpha_cdf_grid.begin(), alpha_cdf_grid.end()-1, xi_prime);
    return ENDF_interp(alpha_cdf_grid[l_alpha_cdf_ind],
                                 alpha_cdf_grid[u_alpha_cdf_ind],
                                 fit_alphas[alpha_start_ind+l_alpha_cdf_ind],
                                 fit_alphas[alpha_start_ind+u_alpha_cdf_ind],
                                 xi_prime);
}

double CDFFile::calculate_scattering_cosine__(const double &inc_ener, const double &sec_ener, const double &alpha)
{
    return ((inc_ener + sec_ener) - alpha*a0*boltz*temp)/(2*sqrt(inc_ener*sec_ener));
}


void CDFFile::all_sample(const double &inc_ener){
    #pragma omp parallel for
    for (int i = 0; i < sample_num_samples; ++i){
        std::pair<double, double> results = single_sample(inc_ener, xi_1[i], xi_2[i]);
        sampled_secondary_energies[i] = results.first;
        sampled_scattering_cosines[i] = results.second;
    }
}

void CDFFile::write_results(){
    // H5::FileCreatPropList fcpl;
    // H5::FileAccPropList fapl;
    // H5::H5File file(sample_output_file, H5F_ACC_TRUNC, fcpl, fapl);

    // writeHDF5Int(file, za, "ZA");
    // writeHDF5Int(file, mat, "MAT");
    // writeHDF5Double(file, a0, "A0");
    // writeHDF5Double(file, e_max, "E_MAX");
    // writeHDF5Double(file, m0, "M0");
    // writeHDF5Double(file, free_xs, "FREE_XS");
    // writeHDF5Double(file, bound_xs, "BOUND_XS");

    // writeHDF5Int(file, xi_1.size(), "Number of Samples");
    // writeHDF5Double(file, temp, "Sampling Temperature");
    // writeHDF5Double(file, time_to_sample_ms, "Sampling Time [ms]");

    // if (!sample_only_timing_results){
    //     writeHDF5DoubleVector(file, sampled_secondary_energies, "Sampled Energies");
    //     writeHDF5DoubleVector(file, sampled_scattering_cosines, "Sampled Cosines");
    // }
    // file.close();
}

void sample_cdf(){
    CDFFile data(sample_input_file);

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
        std::cout << "Time to write the CDF sampling results coefficients | milliseconds " << file_write_duration.count() << std::endl;
    }
}