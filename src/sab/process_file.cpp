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

// Class constructor
DistData::DistData(TslFileData& file_data){
    za = file_data.za;
    mat = file_data.mat;
    temp = file_data.temp;
    t_eff = file_data.t_eff;
    temp_ratio = file_data.temp_ratio;
    a0 = file_data.a0;
    e_max = file_data.e_max;
    m0 = file_data.m0;
    free_xs = file_data.free_xs;
    bound_xs = file_data.bound_xs;

    alphas = file_data.return_scaled_alphas();
    betas = file_data.return_full_scaled_betas();
    half_betas = file_data.return_scaled_betas();
    tsl_vals = file_data.return_full_asym_tsl_vals();

    beta_grid = file_data.return_betas();

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

// Private Methods

double DistData::__asym_SCT_alpha_integral_bounds__(double const& alpha, double const& beta){
    double abs_b = abs(beta);
    double two_sqrt_ar = 2*sqrt(alpha*temp_ratio);
    double erfc_1 = erfc((abs_b-alpha)/two_sqrt_ar);
    double erfc_2 = erfc((abs_b+alpha)/two_sqrt_ar);
    double inner_exp = exp(beta/(std::copysign(temp_ratio, beta)));
    double outer_exp = exp(-(abs_b/2)-(beta/2));
    return 0.5*(outer_exp*(erfc_1 - inner_exp*erfc_2));
}

double DistData::__calculate_beta_min__(double const& inc_energy){
    return -(inc_energy)/(boltz*temp);
}

double DistData::__calculate_beta_max__(double const& inc_energy){
    return beta_max;
}

std::pair<double, double> DistData::__calculate_alpha_extrema__(double const& inc_energy, double const& beta){
    double t1 = sqrt(inc_energy);
    double t2 = sqrt(abs(inc_energy + beta*boltz*temp));
    double t3 = a0*boltz*temp;
    return std::make_pair(std::max(alpha_min, pow((t1 - t2), 2)/t3), pow((t1 + t2), 2)/t3);
}

// Public Methods

double DistData::return_sym_SCT(double const& alpha, double const& beta){
    double numer_numer = pow((alpha-abs(beta)), 2);
    double numer_denom = 4*alpha*temp_ratio;
    double numer = exp(-(numer_numer/numer_denom) - (abs(beta)/2));
    double denom = sqrt(4*PI*alpha*temp_ratio);
    return numer/denom;
}

double DistData::return_asym_SCT(double const& alpha, double const& beta){
    return exp(-beta/2) * return_sym_SCT(alpha, beta);
}

double DistData::return_asym_SCT_alpha_integral(double const& alpha_l, double const& alpha_u, double const& beta){
    double l = __asym_SCT_alpha_integral_bounds__(alpha_l, beta);
    double u = __asym_SCT_alpha_integral_bounds__(alpha_u, beta);
    return u-l;
}

std::pair<double, bool> DistData::return_arbitrary_TSL_val(double const& alpha, double const& beta){
    // NOTE: Don't have to evaluate teh SCT since I use an analytic form for the integral
    bool off_data = (alpha>alphas.back() || beta<betas.front() || beta > betas.back());
    if (off_data){
        return std::make_pair(return_asym_SCT(alpha, beta), true);
    }
    else {
        int alpha_lo_insert = std::lower_bound(alphas.begin()+1, alphas.end(), alpha) - alphas.begin();
        int beta_lo_insert = std::lower_bound(betas.begin()+1, betas.end(), beta) - betas.begin();
        double& f11 = tsl_vals[beta_lo_insert-1][alpha_lo_insert-1];
        double& f12 = tsl_vals[beta_lo_insert-1][alpha_lo_insert];
        double& f21 = tsl_vals[beta_lo_insert][alpha_lo_insert-1];
        double& f22 = tsl_vals[beta_lo_insert][alpha_lo_insert];
        bool below_cutoff = (f11<sct_cutoff || f12<sct_cutoff || f21<sct_cutoff || f22<sct_cutoff);
        if (below_cutoff){
            return std::make_pair(return_asym_SCT(alpha, beta), true);
        }
        else{
            double& b_l = betas[beta_lo_insert-1];
            double& b_u = betas[beta_lo_insert];
            double& a_l = alphas[alpha_lo_insert-1];
            double& a_u = alphas[alpha_lo_insert];
            return std::make_pair(bi_interp(b_l, b_u, a_l, a_u,
                                             f11, f12, f21, f22,
                                             beta, alpha,
                                             beta_interpolation_scheme, alpha_interpolation_scheme), 
                                             false);
        }
    }       
}

std::vector<double> DistData::__get_viable_betas__(double const& inc_energy){
    double b_min = __calculate_beta_min__(inc_energy);
    double b_max = __calculate_beta_max__(inc_energy);
    auto lo_insert = std::lower_bound(betas.begin(), betas.end(), b_min) - betas.begin();
    auto hi_insert = std::lower_bound(betas.begin(), betas.end(), b_max) - betas.begin();
    std::vector<double> result;
    result.reserve(hi_insert - lo_insert + 2);
    result.push_back(b_min);
    for (int i=lo_insert; i<hi_insert; i++){
        result.push_back(betas[i]);
    }
    result.push_back(b_max);
    return result;
}

std::vector<double> DistData::__get_viable_alphas__(double const& inc_energy, double const& beta){
    auto [a_min, a_max] = __calculate_alpha_extrema__(inc_energy, beta);
    auto lo_insert = std::lower_bound(alphas.begin(), alphas.end(), a_min) - alphas.begin();
    auto hi_insert = std::lower_bound(alphas.begin(), alphas.end(), a_max) - alphas.begin();
    std::vector<double> result;
    result.reserve(hi_insert - lo_insert + 2);
    result.push_back(a_min);
    for (int i=lo_insert; i<hi_insert; i++){
        result.push_back(alphas[i]);
    }
    result.push_back(a_max);
    return result;
}

std::pair<std::vector<double>, std::vector<bool>> DistData::__get_alpha_line__(std::vector<double> const& alpha_vals, double const& beta){
    std::vector<double> vals;
    std::vector<bool> truthy;
    vals.reserve(alpha_vals.size());
    truthy.reserve(alpha_vals.size());
    for(double alpha:alpha_vals){
        auto [val, thruth] = return_arbitrary_TSL_val(alpha, beta);
        vals.push_back(val);
        truthy.push_back(thruth);
    }
    return std::make_pair(vals, truthy);
}

double DistData::__integrate_alpha_line__(std::vector<double> const& alpha_vals, std::vector<double> const& vals, std::vector<bool> const& truthy, double const& beta){
    double integral = 0;
    for(int i=0; i<alpha_vals.size()-1; i++){
        if (truthy[i] || truthy[i+1]){
            integral += return_asym_SCT_alpha_integral(alpha_vals[i], alpha_vals[i+1], beta);            
        }
        else{
            integral += ENDF_integrate(alpha_vals[i], alpha_vals[i+1], vals[i], vals[i+1], alpha_integration_scheme);
        }
    }
    return integral;
}

double DistData::__get_beta_pdf_val__(double const& inc_energy, double const& beta){
    std::vector<double> alpha_vals = __get_viable_alphas__(inc_energy, beta);
    auto [vals, truthy] = __get_alpha_line__(alpha_vals, beta);
    return __integrate_alpha_line__(alpha_vals, vals, truthy, beta);
}

double DistData::__wrapper_get_beta_pdf_val__(double const& beta){
    return __get_beta_pdf_val__(__inc_ener_hold__, beta);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_beta_pdf(double const& inc_energy){
    std::vector<double> beta_vals = __get_viable_betas__(inc_energy);
    std::vector<double> beta_pdf;
    beta_pdf.reserve(beta_vals.size());
    for (double beta: beta_vals){
        beta_pdf.push_back(__get_beta_pdf_val__(inc_energy, beta));
    }
    return std::make_pair(beta_vals, beta_pdf);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_linearized_beta_pdf(double const& inc_energy){
    __inc_ener_hold__ = inc_energy;
    std::vector<double> beta_vals = __get_viable_betas__(inc_energy);
    std::vector<double> beta_pdf;
    beta_pdf.reserve(beta_vals.size());
    for (double beta: beta_vals){
        beta_pdf.push_back(__get_beta_pdf_val__(inc_energy, beta));
    }
    auto get_new_beta_pdf_val = [&](double x) {return __wrapper_get_beta_pdf_val__(x);};
    linearize(beta_vals, beta_pdf, get_new_beta_pdf_val);
    return std::make_pair(beta_vals, beta_pdf);
}

double DistData::return_ii_xs_value(double const& inc_energy){
    // auto [beta_vals, beta_pdf] = return_beta_pdf(inc_energy);
    auto [beta_vals, beta_pdf] = return_linearized_beta_pdf(inc_energy);
    // std::cout << inc_energy << std::endl;
    return ((a0*boltz*temp*bound_xs)/(4*inc_energy))*ENDF_integrate_vector(beta_vals, beta_pdf, beta_integration_scheme);
}

std::vector<double> DistData::return_ii_xs_vector(std::vector<double> const& inc_energies){
    std::vector<double> result(inc_energies.size());
    for (int i=0; i<inc_energies.size(); i++){
        result[i] = return_ii_xs_value(inc_energies[i]);
    }
    return result;
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_linearized_ii_xs(){
    std::vector<double> energies = logspace(e_min, e_max, 100);
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

void DistData::__get_beta_sampling_dists__(){
    beta_vals.reserve(inc_energy_grid.size());
    beta_pdfs.reserve(inc_energy_grid.size());
    beta_cdfs.reserve(inc_energy_grid.size());
    fit_beta_vals.reserve(inc_energy_grid.size());
    for (auto inc_energy: inc_energy_grid){
        auto [vals, pdf] = return_linearized_beta_pdf(inc_energy);
        beta_vals.push_back(vals);
        beta_pdfs.push_back(pdf);
        beta_cdfs.push_back(pdf_to_cdf(vals, pdf));
        fit_beta_vals.push_back(fit_cdf(vals, beta_cdfs.back(), beta_cdf_grid));
    }
}

double DistData::__wrapper_get_alpha_pdf_val__(double const& alpha){
    auto [val, truthy] = return_arbitrary_TSL_val(alpha, __beta_hold__);
    return val;
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_linearized_alpha_pdf(double const& beta){
    __beta_hold__ = beta;
    std::vector<double> a_vals = alphas;
    auto [alpha_pdf, truthy] = __get_alpha_line__(a_vals, __beta_hold__);
    auto get_new_alpha_pdf_val = [&](double x) {return __wrapper_get_alpha_pdf_val__(x);};
    linearize(a_vals, alpha_pdf, get_new_alpha_pdf_val);
    return std::make_pair(a_vals, alpha_pdf);
}

std::pair<std::vector<double>, std::vector<double>> DistData::return_viable_linearized_alpha_pdf(double const& inc_energy, double const& beta){
    __beta_hold__ = beta;
    std::vector<double> a_vals = __get_viable_alphas__(inc_energy, beta);
    auto [alpha_pdf, truthy] = __get_alpha_line__(a_vals, __beta_hold__);
    auto get_new_alpha_pdf_val = [&](double x) {return __wrapper_get_alpha_pdf_val__(x);};
    linearize(a_vals, alpha_pdf, get_new_alpha_pdf_val);
    return std::make_pair(a_vals, alpha_pdf);
}

void DistData::__get_alpha_sampling_dists__(){
    // NOTE: Beta grid for storage is determined at initialization and is set to the leapr input grid
    // NOTE: Alpha distributions are symmetric about b=0 so only do the positive half
    alpha_vals.reserve(beta_grid.size());
    alpha_pdfs.reserve(beta_grid.size());
    alpha_cdfs.reserve(beta_grid.size());
    fit_alpha_vals.reserve(beta_grid.size());
    for (auto beta: half_betas){
        auto [vals, pdf] = return_linearized_alpha_pdf(beta);
        alpha_vals.push_back(vals);
        alpha_pdfs.push_back(pdf);
        alpha_cdfs.push_back(pdf_to_cdf(vals, pdf));
        fit_alpha_vals.push_back(fit_cdf(vals, alpha_cdfs.back(), alpha_cdf_grid));
    }
}

void DistData::calculate_sampling_dists(){
    auto [ene, xs] = return_final_ii_xs();
    inc_energy_grid = ene;
    ii_xs = xs;
    __get_beta_sampling_dists__();
    __get_alpha_sampling_dists__();
}

double DistData::beta_to_outgoing_energy(double const& inc_energy, double const& beta){
    return inc_energy + temp*boltz*beta;
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
    return (out_energy - inc_energy)/(boltz*temp);
}

double DistData::alpha_to_scattering_angle(double const& inc_energy, double const& out_energy, double const& alpha){
    double t1 = inc_energy + out_energy;
    double t2 = alpha*a0*boltz*temp;
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