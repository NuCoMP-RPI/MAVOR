#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <filesystem>

#include "constants.hpp"
#include "integration.hpp"
#include "interpolation.hpp"
#include "file_read.hpp"
#include "process_file.hpp"
#include "utilities.hpp"
#include "linearize.hpp"

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
    tsl_vals = file_data.return_full_asym_tsl_vals();
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
        // check may not be needed in practice
        if (alpha_lo_insert == 0){alpha_lo_insert++; std::cout << "alpha_lo_insert was zero." << std::endl;}
        // check may not be needed in practice
        int beta_lo_insert = std::lower_bound(betas.begin()+1, betas.end(), beta) - betas.begin();
        if (beta_lo_insert == 0){beta_lo_insert++; std::cout << "bets_lo_insert was zero." << std::endl;}
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
    std::cout << inc_energy << std::endl;
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
    std::vector<double> energies = logspace(e_min, e_max, 10);
    std::vector<double> xs(energies.size());
    for (int i=0; i<energies.size(); i++){
        xs[i] = return_ii_xs_value(energies[i]);
    }
    auto get_new_xs = [&](double x) {return return_ii_xs_value(x);};
    linearize(energies, xs, get_new_xs);
    return std::make_pair(energies, xs);
}

void DistData::__get_beta_sampling_dists__(){
    beta_vals.reserve(inc_energy_grid.size());
    beta_pdfs.reserve(inc_energy_grid.size());
    for (auto inc_energy: inc_energy_grid){
        auto [vals, pdf] = return_linearized_beta_pdf(inc_energy);
        beta_vals.push_back(vals);
        beta_pdfs.push_back(pdf);
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

void DistData::__get_alpha_sampling_dists__(){
    alpha_vals.reserve(beta_grid.size());
    alpha_pdfs.reserve(beta_grid.size());
    for (auto beta: beta_grid){
        auto [vals, pdf] = return_linearized_alpha_pdf(beta);
        alpha_vals.push_back(vals);
        alpha_pdfs.push_back(pdf);        
    }
}

void DistData::calculate_sampling_dists(){
    auto [ene, xs] = return_linearized_ii_xs();
    inc_energy_grid = ene;
    ii_xs = xs;
    beta_grid = betas;
    __get_beta_sampling_dists__();
    __get_alpha_sampling_dists__();
}

void print_array(std::vector<double> array){
    for(auto val: array){
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void print_matrix(std::vector<std::vector<double>> matrix){
    for(auto vec:matrix){
        for(auto val:vec){
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void process_file(const std::string& file_path){
    std::cout << file_path << '\n';
    TslFileData file_data(file_path);
    DistData dist_data(file_data);
    // auto [energies, xs] = dist_data.return_linearized_beta_pdf(4);
    // auto [energies, xs] = dist_data.return_linearized_ii_xs();
    // dist_data.return_ii_xs_value(4);

    dist_data.calculate_sampling_dists();

    std::ofstream file("Results.csv");
    file << "x, y" << std::endl;
    for (int i=0; i<dist_data.inc_energy_grid.size(); i++){
        file << dist_data.inc_energy_grid[i] << "," << dist_data.ii_xs[i] << std::endl;
    }
    file.close();
}