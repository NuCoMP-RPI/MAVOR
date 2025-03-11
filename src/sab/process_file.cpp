#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <set>

#include "constants.hpp"
#include "integration.hpp"
#include "interpolation.hpp"
#include "file_read.hpp"
#include "file_write.hpp"
#include "process_file.hpp"
#include "utilities.hpp"
#include "runtime_variables.hpp"
#include "linearize.hpp"
#include "energy_grid.hpp"

#include <iostream>
#include <vector>

void read_cdf_file__(std::string const & file_path, std::vector<double> &grid){
    std::fstream file(file_path);
    std::string line;
    while (getline(file, line))
    {
        // right trim the line, should only be one value per line
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        grid.push_back(std::stod(line));
    }
}

// Class constructor
DistData::DistData(TslFileData& file_data) : tsl_data(file_data){
    beta_grid = tsl_data.return_betas();
    calculation_alphas = tsl_data.return_scaled_alphas();
    calculation_betas = tsl_data.return_full_scaled_betas();
    calculation_half_betas = tsl_data.return_scaled_betas();
    calculation_tsl_vals = tsl_data.return_full_asym_tsl_vals();

    set_interp_integration_schemes__();
    set_initial_cdf_grids__();
}

void DistData::set_interp_integration_schemes__(){
    /// NOTE: Due to the handling of TSL data, these schemes may be unreliable.
    /// Alpha interpolation and integration will be invalid as long as lln is set in the tsl data (ln(s) instead of s is stored) and interpolation cannot be altered
    /// Some considerations have been taken but not guaranteed to be valid
    /// Beta interpolation and integration will be invalid as long as lasym is set in the tsl data (symmetric for of s in stored)
    /// All beta interpolation should be handled in file_read.cpp and integration should be done with lin-lin due to linearization routines
    alpha_interpolation_scheme = tsl_data.return_alpha_schemes();
    alpha_integration_scheme = alpha_interpolation_scheme;
    beta_interpolation_scheme = tsl_data.return_beta_schemes();
    /// NOTE: Beta arrays are linearized
    // beta_integration_scheme = beta_interpolation_scheme;
    beta_integration_scheme = 2;
}

void DistData::set_initial_cdf_grids__(){
    if (linearize_cdfs){
        initialization_beta_cdf_grid.push_back(0.0001);
        initialization_beta_cdf_grid.push_back(0.9999);
        initialization_alpha_cdf_grid.push_back(0.0001);
        initialization_alpha_cdf_grid.push_back(0.9999);
    }
    else if (use_sigmoid_cdfs)
    {
        initialization_beta_cdf_grid = sigmoid_space(0, 1, num_beta_cdf_points + 2, beta_cdf_extent);
        initialization_alpha_cdf_grid = sigmoid_space(0, 1, num_alpha_cdf_points + 2, alpha_cdf_extent);

        // Trim off the 0 and 1 for the cdf grids
        // Including them causes trouble with the fitting across multiple temperatures as finding fit points at 0 and 1 cause
        // large spikes as the edges of the fit values
        initialization_beta_cdf_grid.erase(initialization_beta_cdf_grid.begin());
        initialization_beta_cdf_grid.erase(initialization_beta_cdf_grid.end()-1);
        initialization_alpha_cdf_grid.erase(initialization_alpha_cdf_grid.begin());
        initialization_alpha_cdf_grid.erase(initialization_alpha_cdf_grid.end()-1);
    }
    else
    {
        read_cdf_file__(alpha_cdf_grid_loc, initialization_alpha_cdf_grid);
        read_cdf_file__(beta_cdf_grid_loc, initialization_beta_cdf_grid);
    }
     
}

// std::pair<double, bool> DistData::return_arbitrary_TSL_val(double const &alpha, double const &beta)
// {
//     bool off_data = (
//         alpha > calculation_alphas.back() || 
//         beta  < calculation_betas.front() || 
//         beta  > calculation_betas.back()
//         );
//     if (off_data){
//         return std::make_pair(tsl_data.return_asym_SCT(alpha, beta), true);
//     }
//     else {
//         int alpha_lo_insert = std::lower_bound(calculation_alphas.begin()+1, calculation_alphas.end(), alpha) - calculation_alphas.begin();
//         int beta_lo_insert = std::lower_bound(calculation_betas.begin()+1, calculation_betas.end(), beta) - calculation_betas.begin();
//         double& f11 = calculation_tsl_vals[beta_lo_insert-1][alpha_lo_insert-1];
//         double& f12 = calculation_tsl_vals[beta_lo_insert-1][alpha_lo_insert];
//         double& f21 = calculation_tsl_vals[beta_lo_insert][alpha_lo_insert-1];
//         double& f22 = calculation_tsl_vals[beta_lo_insert][alpha_lo_insert];
//         bool below_cutoff = (f11<sct_cutoff || f12<sct_cutoff || f21<sct_cutoff || f22<sct_cutoff);
//         if (below_cutoff){
//             return std::make_pair(tsl_data.return_asym_SCT(alpha, beta), true);
//         }
//         else{
//             double& b_l = calculation_betas[beta_lo_insert-1];
//             double& b_u = calculation_betas[beta_lo_insert];
//             double& a_l = calculation_alphas[alpha_lo_insert-1];
//             double& a_u = calculation_alphas[alpha_lo_insert];
//             return std::make_pair(bi_interp(b_l, b_u, a_l, a_u,
//                                              f11, f12, f21, f22,
//                                              beta, alpha,
//                                              beta_interpolation_scheme, alpha_interpolation_scheme), 
//                                              false);
//         }
//     }
// }

std::vector<double> DistData::get_viable_betas__(double const& inc_energy){
    double b_min = tsl_data.calculate_beta_min(inc_energy);
    double b_max = tsl_data.calculate_beta_max(inc_energy);
    auto lo_insert = std::lower_bound(calculation_betas.begin(), calculation_betas.end(), b_min) - calculation_betas.begin();
    auto hi_insert = std::lower_bound(calculation_betas.begin(), calculation_betas.end(), b_max) - calculation_betas.begin();
    std::vector<double> result;
    result.reserve(hi_insert - lo_insert + 2);
    result.push_back(b_min);
    for (int i=lo_insert; i<hi_insert; i++){
        result.push_back(calculation_betas[i]);
    }
    result.push_back(b_max);
    return result;
}

std::vector<double> DistData::get_viable_alphas__(double const &inc_energy, double const &beta){
    auto [a_min, a_max] = tsl_data.calculate_alpha_extrema(inc_energy, beta);
    auto lo_insert = std::lower_bound(calculation_alphas.begin(), calculation_alphas.end(), a_min) - calculation_alphas.begin();
    auto hi_insert = std::lower_bound(calculation_alphas.begin(), calculation_alphas.end(), a_max) - calculation_alphas.begin();
    std::vector<double> result;
    result.reserve(hi_insert - lo_insert + 2);
    result.push_back(a_min);
    for (int i=lo_insert; i<hi_insert; i++){
        result.push_back(calculation_alphas[i]);
    }
    result.push_back(a_max);
    return result;
}

std::pair<std::vector<double>, std::vector<bool>> DistData::get_alpha_line__(std::vector<double> const& alpha_vals, double const& beta){
    std::vector<double> vals;
    std::vector<bool> truthy;
    vals.reserve(alpha_vals.size());
    truthy.reserve(alpha_vals.size());
    for(double alpha:alpha_vals){
        auto [val, thruth] = tsl_data.return_arbitrary_TSL_val(alpha, beta);
        vals.push_back(val);
        truthy.push_back(thruth);
    }
    return std::make_pair(vals, truthy);
}

double DistData::integrate_alpha_line__(std::vector<double> const& alpha_vals, std::vector<double> const& vals, std::vector<bool> const& truthy, double const& beta){
    double integral = 0;
    for(int i=0; i<alpha_vals.size()-1; i++){
        if (truthy[i] || truthy[i+1]){
            integral += tsl_data.return_asym_SCT_alpha_integral(alpha_vals[i], alpha_vals[i+1], beta);
        }
        else{
            /// NOTE: This function will probably need to be moved inside tsl_data in order to properly integrate
            integral += ENDF_integrate(alpha_vals[i], alpha_vals[i+1], vals[i], vals[i+1], alpha_integration_scheme);
        }
    }
    return integral;
}

double DistData::get_beta_pdf_val__(double const& inc_energy, double const& beta){
    std::vector<double> alpha_vals = get_viable_alphas__(inc_energy, beta);
    auto [vals, truthy] = get_alpha_line__(alpha_vals, beta);
    return integrate_alpha_line__(alpha_vals, vals, truthy, beta);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_beta_pdf(double const& inc_energy){
    std::vector<double> beta_vals = get_viable_betas__(inc_energy);
    std::vector<double> beta_pdf;
    beta_pdf.reserve(beta_vals.size());
    for (double beta: beta_vals){
        beta_pdf.push_back(get_beta_pdf_val__(inc_energy, beta));
    }
    return std::make_pair(beta_vals, beta_pdf);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_linearized_beta_pdf(double const& inc_energy){
    auto [beta_vals, beta_pdf] = return_beta_pdf(inc_energy);
    auto get_new_beta_pdf_val = [this, inc_energy](double beta) {return get_beta_pdf_val__(inc_energy, beta);};
    linearize(beta_vals, beta_pdf, get_new_beta_pdf_val, 0.1, 0.001);
    return std::make_pair(beta_vals, beta_pdf);
}

double DistData::return_ii_xs_value(double const& inc_energy){
    auto [beta_vals, beta_pdf] = return_linearized_beta_pdf(inc_energy);
    return ((tsl_data.a0*boltz*tsl_data.temp*tsl_data.bound_xs)/(4*inc_energy))*ENDF_integrate_vector(beta_vals, beta_pdf, beta_integration_scheme);
}

std::vector<double> DistData::return_ii_xs_vector(std::vector<double> const& inc_energies){
    std::vector<double> result(inc_energies.size());
    for (int i=0; i<inc_energies.size(); i++){
        result[i] = return_ii_xs_value(inc_energies[i]);
    }
    return result;
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_linearized_ii_xs(){
    std::vector<double> energies = logspace(e_min, tsl_data.e_max, 52); // Don't know what the best choice for starting grid would be or how many points
    std::vector<double> xs = return_ii_xs_vector(energies);
    auto get_new_xs = [&](double x) {return return_ii_xs_value(x);};
    linearize(energies, xs, get_new_xs, 1000, 0.01); // Only consider the relative difference as important
    return std::make_pair(energies, xs);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_final_ii_xs(){
    if (use_external_energy_grid || use_internal_energy_grid)
    {
        std::vector<double> energies = return_incident_energy_grid();
        std::vector<double> xs = return_ii_xs_vector(energies);
        return std::make_pair(energies, xs);
    }
    else
    {
        return return_linearized_ii_xs();
    }
}

void DistData::get_beta_sampling_dists__(){
    calculation_beta_vals.reserve(incident_energy_grid.size());
    calculation_beta_cdfs.reserve(incident_energy_grid.size());
    beta_vals.reserve(incident_energy_grid.size());
    for (auto inc_energy: incident_energy_grid){
        auto [vals, pdf] = return_linearized_beta_pdf(inc_energy);
        calculation_beta_vals.push_back(vals);
        calculation_beta_cdfs.push_back(pdf_to_cdf(vals, pdf));
        beta_vals.push_back(fit_cdf(vals, calculation_beta_cdfs.back(), initialization_beta_cdf_grid));
        beta_cdf_grid.push_back(initialization_beta_cdf_grid);
    }
}

void DistData::linearize_beta_sampling_dists__(){
    for (int i = 0; i < calculation_beta_cdfs.size(); i++){
        // Lambda function to get a new beta value that corresponds to a desired cdf value
       auto get_new_cdf_point = [&](double desired_cdf_val){
            int cdf_insert = std::lower_bound(calculation_beta_cdfs[i].begin()+1, calculation_beta_cdfs[i].end(), desired_cdf_val) - calculation_beta_cdfs[i].begin();
            return ENDF_interp(calculation_beta_cdfs[i][cdf_insert],
                               calculation_beta_cdfs[i][cdf_insert+1],
                               calculation_beta_vals[i][cdf_insert],
                               calculation_beta_vals[i][cdf_insert+1],
                               desired_cdf_val);
        };
        linearize(beta_cdf_grid[i], beta_vals[i], get_new_cdf_point, 0.1, 0.001);
    }
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_linearized_alpha_pdf(double const& beta){
    std::vector<double> a_vals = calculation_alphas;
    auto [alpha_pdf, truthy] = get_alpha_line__(a_vals, beta);
    auto get_new_alpha_pdf_val = [this, beta](double alpha) {return tsl_data.return_arbitrary_TSL_val(alpha, beta).first;};
    linearize(a_vals, alpha_pdf, get_new_alpha_pdf_val, 0.1, 0.001);
    return std::make_pair(a_vals, alpha_pdf);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_viable_linearized_alpha_pdf(double const& inc_energy, double const& beta){
    std::vector<double> a_vals = get_viable_alphas__(inc_energy, beta);
    auto [alpha_pdf, truthy] = get_alpha_line__(a_vals, beta);
    auto get_new_alpha_pdf_val = [this, beta](double alpha) {return tsl_data.return_arbitrary_TSL_val(alpha, beta).first;};
    linearize(a_vals, alpha_pdf, get_new_alpha_pdf_val, 0.1, 0.001);
    return std::make_pair(a_vals, alpha_pdf);
}

void DistData::get_alpha_sampling_dists__(){
    /// NOTE: Beta grid for storage is determined at initialization and is set to the leapr input grid and is not used here
    /// NOTE: Alpha distributions are symmetric about b=0 so only do the positive half
    /// NOTE: Ensure that you are using the scaled half betas for calculation
    calculation_alpha_vals.reserve(beta_grid.size());
    calculation_alpha_cdfs.reserve(beta_grid.size());
    alpha_vals.reserve(beta_grid.size());
    for (auto beta: calculation_half_betas){
        auto [vals, pdf] = return_linearized_alpha_pdf(beta);
        calculation_alpha_vals.push_back(vals);
        calculation_alpha_cdfs.push_back(pdf_to_cdf(vals, pdf));
        alpha_vals.push_back(fit_cdf(vals, calculation_alpha_cdfs.back(), initialization_alpha_cdf_grid));
        alpha_cdf_grid.push_back(initialization_alpha_cdf_grid);
    }
}

void DistData::linearize_alpha_sampling_dists__(){
    for (int i = 0; i < calculation_alpha_cdfs.size(); i++){
        // Lambda function to get a new beta value that corresponds to a desired cdf value
       auto get_new_cdf_point = [&](double desired_cdf_val){
            int cdf_insert = std::lower_bound(calculation_alpha_cdfs[i].begin()+1, calculation_alpha_cdfs[i].end(), desired_cdf_val) - calculation_alpha_cdfs[i].begin();
            return ENDF_interp(calculation_alpha_cdfs[i][cdf_insert],
                               calculation_alpha_cdfs[i][cdf_insert+1],
                               calculation_alpha_vals[i][cdf_insert],
                               calculation_alpha_vals[i][cdf_insert+1],
                               desired_cdf_val);
        };
        linearize(alpha_cdf_grid[i], alpha_vals[i], get_new_cdf_point, 0.1, 0.001);
    }
}

void DistData::calculate_sampling_dists(){
    auto [ene, xs] = return_final_ii_xs();
    incident_energy_grid = ene;
    cross_section = xs;
    get_beta_sampling_dists__();
    get_alpha_sampling_dists__();
    if (linearize_cdfs){
        if (!silence){std::cout << "Linearizing sampling distributions" << std::endl;}
        linearize_beta_sampling_dists__();
        linearize_alpha_sampling_dists__();
    }
}

double DistData::beta_to_outgoing_energy(double const& inc_energy, double const& beta){
    return inc_energy + tsl_data.temp*boltz*beta;
}

std::vector<double> DistData::betas_to_outgoing_energies(double const& inc_energy, std::vector<double> const& betas){
    std::vector<double> outs;
    outs.reserve(betas.size());
    for (double beta:betas){
        outs.push_back(beta_to_outgoing_energy(inc_energy, beta));
    }
    return outs;
}

double DistData::return_beta(double const& inc_energy, double const& out_energy){
    return (out_energy - inc_energy)/(boltz*tsl_data.temp);
}

double DistData::alpha_to_scattering_angle(double const& inc_energy, double const& out_energy, double const& alpha){
    double t1 = inc_energy + out_energy;
    double t2 = alpha*tsl_data.a0*boltz*tsl_data.temp;
    double t3 = 2*sqrt(inc_energy*out_energy);
    return (t1 - t2)/t3;
}

std::vector<double> DistData::alphas_to_scatting_angles(double const& inc_energy, double const& out_energy, std::vector<double> const& alphas){
    std::vector<double> angles;
    angles.reserve(alphas.size());
    for (double alpha:alphas){
        angles.push_back(alpha_to_scattering_angle(inc_energy, out_energy, alpha));
    }
    return angles;
}