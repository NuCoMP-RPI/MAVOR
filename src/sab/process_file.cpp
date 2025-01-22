#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <filesystem>
#include <chrono>

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
#include <H5Cpp.h>

// Class constructor
DistData::DistData(TslFileData& file_data) : tsl_data(file_data){
    beta_grid = tsl_data.return_betas();
    calculation_alphas = tsl_data.return_scaled_alphas();
    calculation_betas = tsl_data.return_full_scaled_betas();
    calculation_half_betas = tsl_data.return_scaled_betas();

    beta_cdf_grid = sigmoid_space(0, 1, num_beta_cdf_points + 2, beta_cdf_extent);
    alpha_cdf_grid = sigmoid_space(0, 1, num_alpha_cdf_points + 2, alpha_cdf_extent);

    // Trim off the 0 and 1 for the cdf grids
    // Including them causes trouble with the fitting across multiple temperatures as finding fit points at 0 and 1 cause
    // large spikes as the edges of the fit values
    beta_cdf_grid.erase(beta_cdf_grid.begin());
    beta_cdf_grid.erase(beta_cdf_grid.end()-1);
    alpha_cdf_grid.erase(alpha_cdf_grid.begin());
    alpha_cdf_grid.erase(alpha_cdf_grid.end()-1);
}

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

std::vector<double> DistData::get_viable_alphas__(double const& inc_energy, double const& beta){
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
            /// NOTE: The alpha integration scheme is not set properly, it needs to reflect the storage interpolation scheme
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

double DistData::wrapper_get_beta_pdf_val__(double const& beta){
    return get_beta_pdf_val__(inc_ener_hold__, beta);
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
    inc_ener_hold__ = inc_energy;
    std::vector<double> beta_vals = get_viable_betas__(inc_energy);
    std::vector<double> beta_pdf;
    beta_pdf.reserve(beta_vals.size());
    for (double beta: beta_vals){
        beta_pdf.push_back(get_beta_pdf_val__(inc_energy, beta));
    }
    auto get_new_beta_pdf_val = [&](double x) {return wrapper_get_beta_pdf_val__(x);};
    linearize(beta_vals, beta_pdf, get_new_beta_pdf_val);
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
    std::vector<double> energies = logspace(e_min, tsl_data.e_max, 100);
    std::vector<double> xs = return_ii_xs_vector(energies);
    auto get_new_xs = [&](double x) {return return_ii_xs_value(x);};
    linearize(energies, xs, get_new_xs);
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
    std::vector<std::vector<double>> beta_vals_dist(incident_energy_grid.size());
    std::vector<std::vector<double>> beta_pdfs_dist(incident_energy_grid.size());
    std::vector<std::vector<double>> beta_cdfs_dist(incident_energy_grid.size());
    beta_vals.reserve(incident_energy_grid.size());
    for (auto inc_energy: incident_energy_grid){
        auto [vals, pdf] = return_linearized_beta_pdf(inc_energy);
        beta_vals_dist.push_back(vals);
        beta_pdfs_dist.push_back(pdf);
        beta_cdfs_dist.push_back(pdf_to_cdf(vals, pdf));
        beta_vals.push_back(fit_cdf(vals, beta_cdfs_dist.back(), beta_cdf_grid));
    }
}

double DistData::wrapper_get_alpha_pdf_val__(double const& alpha){
    auto [val, truthy] = tsl_data.return_arbitrary_TSL_val(alpha, beta_hold__);
    return val;
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_linearized_alpha_pdf(double const& beta){
    beta_hold__ = beta;
    std::vector<double> a_vals = calculation_alphas;
    auto [alpha_pdf, truthy] = get_alpha_line__(a_vals, beta_hold__);
    auto get_new_alpha_pdf_val = [&](double x) {return wrapper_get_alpha_pdf_val__(x);};
    linearize(a_vals, alpha_pdf, get_new_alpha_pdf_val);
    return std::make_pair(a_vals, alpha_pdf);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_viable_linearized_alpha_pdf(double const& inc_energy, double const& beta){
    beta_hold__ = beta;
    std::vector<double> a_vals = get_viable_alphas__(inc_energy, beta);
    auto [alpha_pdf, truthy] = get_alpha_line__(a_vals, beta_hold__);
    auto get_new_alpha_pdf_val = [&](double x) {return wrapper_get_alpha_pdf_val__(x);};
    linearize(a_vals, alpha_pdf, get_new_alpha_pdf_val);
    return std::make_pair(a_vals, alpha_pdf);
}

void DistData::get_alpha_sampling_dists__(){
    /// NOTE: Beta grid for storage is determined at initialization and is set to the leapr input grid and is not used here
    /// NOTE: Alpha distributions are symmetric about b=0 so only do the positive half
    /// NOTE: Ensure that you are using the scaled half betas for calculation
    std::vector<std::vector<double>> alpha_vals_dist(beta_grid.size());
    std::vector<std::vector<double>> alpha_pdfs_dist(beta_grid.size());
    std::vector<std::vector<double>> alpha_cdfs_dist(beta_grid.size());
    alpha_vals.reserve(beta_grid.size());
    for (auto beta: calculation_half_betas){
        auto [vals, pdf] = return_linearized_alpha_pdf(beta);
        alpha_vals_dist.push_back(vals);
        alpha_pdfs_dist.push_back(pdf);
        alpha_cdfs_dist.push_back(pdf_to_cdf(vals, pdf));
        alpha_vals.push_back(fit_cdf(vals, alpha_cdfs_dist.back(), alpha_cdf_grid, 2));
    }
}

void DistData::calculate_sampling_dists(){
    auto [ene, xs] = return_final_ii_xs();
    incident_energy_grid = ene;
    cross_section = xs;
    get_beta_sampling_dists__();
    get_alpha_sampling_dists__();
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