#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <omp.h>
#include <chrono>

#include "H5Cpp.h"

#include "sample_cdf.hpp"

#include "sample_search.hpp"
#include "runtime_variables.hpp"
#include "constants.hpp"
#include "hdf5_file.hpp"
#include "interpolation.hpp"
#include "scale_basis.hpp"

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

std::pair<double, double> CDFFile::return_alpha_extrema__(const double &inc_ener, const double &beta){
    double t1 = sqrt(inc_ener);
    double t2 = a0*boltz*temp;
    double t3 = sqrt(abs(inc_ener + beta*boltz*temp));
    double t4 = t1 - t3;
    double t5 = t1 + t3;
    return std::pair<double, double>((t4*t4)/t2,(t5*t5)/t2);
}

std::pair<double, double> CDFFile::single_sample(const double &inc_ener, const double &xi_1, const double &xi_2){
    auto [lo_inc_ener_ind, hi_inc_ener_ind] = findSampleInterpolationIndices(inc_ener_grid.begin(), inc_ener_grid.end(), inc_ener);
    auto [lo_beta_cdf_ind, hi_beta_cdf_ind] = findSampleInterpolationIndices(beta_cdf_grid.begin(), beta_cdf_grid.end(), xi_1);
    double beta = bi_interp(inc_ener_grid[lo_inc_ener_ind], // x1
                            inc_ener_grid[hi_inc_ener_ind], // x2
                            beta_cdf_grid[lo_beta_cdf_ind], // y1
                            beta_cdf_grid[hi_beta_cdf_ind], // y2
                            fit_betas[lo_inc_ener_ind*beta_cdf_grid.size() + lo_beta_cdf_ind], //f11
                            fit_betas[lo_inc_ener_ind*beta_cdf_grid.size() + hi_beta_cdf_ind], //f12
                            fit_betas[hi_inc_ener_ind*beta_cdf_grid.size() + lo_beta_cdf_ind], //f21
                            fit_betas[hi_inc_ener_ind*beta_cdf_grid.size() + hi_beta_cdf_ind], //f22
                            inc_ener, // x
                            xi_1); // y

    double secondary_energy = inc_ener + beta*boltz*temp;

    auto [amin, amax] = return_alpha_extrema__(inc_ener, beta);
    
    // Unscale and abs the beta to search the alpha storage beta grid
    double grid_beta = abs(beta * temp/ref_temp_k);

    auto [lo_beta_ind, hi_beta_ind] = findSampleInterpolationIndices(beta_grid.begin(), beta_grid.end(), grid_beta);

    // lo beta
    std::vector<double>::iterator l_alpha_start = fit_alphas.begin() + lo_beta_ind*alpha_cdf_grid.size();
    int l_alpha_start_ind = std::distance(fit_alphas.begin(), l_alpha_start);
    std::vector<double>::iterator l_alpha_end = l_alpha_start + alpha_cdf_grid.size();
    auto [ll_amin_ind, lu_amin_ind] = findSampleInterpolationIndices(l_alpha_start, l_alpha_end, amin);
    double l_amin_cdf = ENDF_interp(fit_alphas[l_alpha_start_ind+ll_amin_ind],
                                    fit_alphas[l_alpha_start_ind+lu_amin_ind],
                                    alpha_cdf_grid[ll_amin_ind],
                                    alpha_cdf_grid[lu_amin_ind],
                                    amin);
    auto [ll_amax_ind, lu_amax_ind] = findSampleInterpolationIndices(l_alpha_start, l_alpha_end, amax);
    double l_amax_cdf = ENDF_interp(fit_alphas[l_alpha_start_ind+ll_amax_ind],
                                    fit_alphas[l_alpha_start_ind+lu_amax_ind],
                                    alpha_cdf_grid[ll_amax_ind],
                                    alpha_cdf_grid[lu_amax_ind],
                                    amax);
    double l_xi_2_prime = scale_value(xi_2, 0, 1, l_amin_cdf, l_amax_cdf);
    auto [ll_alpha_cdf_ind, lu_alpha_cdf_ind] = findSampleInterpolationIndices(alpha_cdf_grid.begin(), alpha_cdf_grid.end(), l_xi_2_prime);
    double l_alpha = ENDF_interp(alpha_cdf_grid[ll_alpha_cdf_ind],
                                 alpha_cdf_grid[lu_alpha_cdf_ind],
                                 fit_alphas[l_alpha_start_ind+ll_alpha_cdf_ind],
                                 fit_alphas[l_alpha_start_ind+lu_alpha_cdf_ind],
                                 l_xi_2_prime);

    // hi beta
    std::vector<double>::iterator u_alpha_start = fit_alphas.begin() + hi_beta_ind*alpha_cdf_grid.size();
    int u_alpha_start_ind = std::distance(fit_alphas.begin(), u_alpha_start);
    std::vector<double>::iterator u_alpha_end = u_alpha_start + alpha_cdf_grid.size();
    auto [ul_amin_ind, uu_amin_ind] = findSampleInterpolationIndices(u_alpha_start, u_alpha_end, amin);
    double u_amin_cdf = ENDF_interp(fit_alphas[u_alpha_start_ind+ul_amin_ind],
                                    fit_alphas[u_alpha_start_ind+uu_amin_ind],
                                    alpha_cdf_grid[ul_amin_ind],
                                    alpha_cdf_grid[uu_amin_ind],
                                    amin);
    auto [ul_amax_ind, uu_amax_ind] = findSampleInterpolationIndices(u_alpha_start, u_alpha_end, amax);
    double u_amax_cdf = ENDF_interp(fit_alphas[u_alpha_start_ind+ul_amax_ind],
                                    fit_alphas[u_alpha_start_ind+uu_amax_ind],
                                    alpha_cdf_grid[ul_amax_ind],
                                    alpha_cdf_grid[uu_amax_ind],
                                    amax);
    double u_xi_2_prime = scale_value(xi_2, 0, 1, u_amin_cdf, u_amax_cdf);
    auto [ul_alpha_cdf_ind, uu_alpha_cdf_ind] = findSampleInterpolationIndices(alpha_cdf_grid.begin(), alpha_cdf_grid.end(), u_xi_2_prime);
    double u_alpha = ENDF_interp(alpha_cdf_grid[ul_alpha_cdf_ind],
                                 alpha_cdf_grid[uu_alpha_cdf_ind],
                                 fit_alphas[u_alpha_start_ind+ul_alpha_cdf_ind],
                                 fit_alphas[u_alpha_start_ind+uu_alpha_cdf_ind],
                                 u_xi_2_prime);

    double alpha = ENDF_interp(beta_grid[lo_beta_ind],
                               beta_grid[hi_beta_ind],
                               l_alpha,
                               u_alpha,
                               grid_beta);

    double scattering_cosine = ((inc_ener + secondary_energy) - alpha*a0*boltz*temp)/(2*sqrt(inc_ener*secondary_energy));


    // Debugging print statements
    // std::cout << "inc_ener_grid size: " << inc_ener_grid.size() << std::endl;
    // std::cout << "beta_cdf_grid size: " << beta_cdf_grid.size() << std::endl;
    // std::cout << "fit_betas size: " << fit_betas.size() << std::endl;
    // std::cout << "beta_grid size: " << beta_grid.size() << std::endl;
    // std::cout << "alpha_cdf_grid size: " << alpha_cdf_grid.size() << std::endl;
    // std::cout << "fit_alphas size: " << fit_alphas.size() << std::endl;

    // // Interpolation indices and their values
    // std::cout << "lo_inc_ener_ind: " << lo_inc_ener_ind << " | hi_inc_ener_ind: " << hi_inc_ener_ind << std::endl;
    // std::cout << "lo_inc_ener value: " << inc_ener_grid[lo_inc_ener_ind] << " | hi_inc_ener value: " << inc_ener_grid[hi_inc_ener_ind] << std::endl;

    // std::cout << "lo_beta_cdf_ind: " << lo_beta_cdf_ind << " | hi_beta_cdf_ind: " << hi_beta_cdf_ind << std::endl;
    // std::cout << "lo_beta_cdf value: " << beta_cdf_grid[lo_beta_cdf_ind] << " | hi_beta_cdf value: " << beta_cdf_grid[hi_beta_cdf_ind] << std::endl;

    // std::cout << "Calculated beta: " << beta << std::endl;

    // std::cout << "amin: " << amin << " | amax: " << amax << std::endl;
    // std::cout << "grid_beta: " << grid_beta << std::endl;

    // std::cout << "lo_beta_ind: " << lo_beta_ind << " | hi_beta_ind: " << hi_beta_ind << std::endl;
    // std::cout << "lo_beta value: " << beta_grid[lo_beta_ind] << " | hi_beta value: " << beta_grid[hi_beta_ind] << std::endl;

    // // Lo beta
    // std::cout << "l_alpha_start index: " << l_alpha_start_ind << std::endl;
    // std::cout << "ll_amin_ind: " << ll_amin_ind << " | lu_amin_ind: " << lu_amin_ind << std::endl;
    // std::cout << "ll_amin value: " << fit_alphas[l_alpha_start_ind+ll_amin_ind] << " | lu_amin value: " << fit_alphas[l_alpha_start_ind+lu_amin_ind] << std::endl;
    // std::cout << "l_amin_cdf: " << l_amin_cdf << std::endl;

    // std::cout << "ll_amax_ind: " << ll_amax_ind << " | lu_amax_ind: " << lu_amax_ind << std::endl;
    // std::cout << "ll_amax value: " << fit_alphas[l_alpha_start_ind+ll_amax_ind] << " | lu_amax value: " << fit_alphas[l_alpha_start_ind+lu_amax_ind] << std::endl;
    // std::cout << "l_amax_cdf: " << l_amax_cdf << std::endl;

    // std::cout << "l_xi_2_prime: " << l_xi_2_prime << std::endl;
    // std::cout << "ll_alpha_cdf_ind: " << ll_alpha_cdf_ind << " | lu_alpha_cdf_ind: " << lu_alpha_cdf_ind << std::endl;
    // std::cout << "ll_alpha_cdf value: " << fit_alphas[l_alpha_start_ind+ll_alpha_cdf_ind] << " | lu_alpha_cdf value: " << fit_alphas[l_alpha_start_ind+lu_alpha_cdf_ind] << std::endl;
    // std::cout << "l_alpha: " << l_alpha << std::endl;

    // // Hi beta
    // std::cout << "u_alpha_start index: " << u_alpha_start_ind << std::endl;
    // std::cout << "ul_amin_ind: " << ul_amin_ind << " | uu_amin_ind: " << uu_amin_ind << std::endl;
    // std::cout << "ul_amin value: " << fit_alphas[u_alpha_start_ind+ul_amin_ind] << " | uu_amin value: " << fit_alphas[u_alpha_start_ind+uu_amin_ind] << std::endl;
    // std::cout << "u_amin_cdf: " << u_amin_cdf << std::endl;

    // std::cout << "ul_amax_ind: " << ul_amax_ind << " | uu_amax_ind: " << uu_amax_ind << std::endl;
    // std::cout << "ul_amax value: " << fit_alphas[u_alpha_start_ind+ul_amax_ind] << " | uu_amax value: " << fit_alphas[u_alpha_start_ind+uu_amax_ind] << std::endl;
    // std::cout << "u_amax_cdf: " << u_amax_cdf << std::endl;

    // std::cout << "u_xi_2_prime: " << u_xi_2_prime << std::endl;
    // std::cout << "ul_alpha_cdf_ind: " << ul_alpha_cdf_ind << " | uu_alpha_cdf_ind: " << uu_alpha_cdf_ind << std::endl;
    // std::cout << "ul_alpha_cdf value: " << fit_alphas[u_alpha_start_ind+ul_alpha_cdf_ind] << " | uu_alpha_cdf value: " << fit_alphas[u_alpha_start_ind+uu_alpha_cdf_ind] << std::endl;
    // std::cout << "u_alpha: " << u_alpha << std::endl;

    // // Final alpha
    // std::cout << "Final alpha: " << alpha << std::endl;


    return std::pair<double, double>(secondary_energy, scattering_cosine);
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
    H5::FileCreatPropList fcpl;
    H5::FileAccPropList fapl;
    H5::H5File file("CDFSamplingResults.h5", H5F_ACC_TRUNC, fcpl, fapl);

    writeHDF5Int(file, za, "ZA");
    writeHDF5Int(file, mat, "MAT");
    writeHDF5Double(file, a0, "A0");
    writeHDF5Double(file, e_max, "E_MAX");
    writeHDF5Double(file, m0, "M0");
    writeHDF5Double(file, free_xs, "FREE_XS");
    writeHDF5Double(file, bound_xs, "BOUND_XS");

    writeHDF5Int(file, xi_1.size(), "Number of Samples");
    writeHDF5Double(file, temp, "Sampling Temperature");
    writeHDF5Double(file, time_to_sample_ms, "Sampling Time [ms]");

    writeHDF5DoubleVector(file, sampled_secondary_energies, "Sampled Energies");
    writeHDF5DoubleVector(file, sampled_scattering_cosines, "Sampled Cosines");

    file.close();
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
    data.write_results();
}