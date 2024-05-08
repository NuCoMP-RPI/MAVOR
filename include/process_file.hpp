#ifndef MAVOR_PROCESS_FILE_H 
#define MAVOR_PROCESS_FILE_H 

#include <iostream>
#include <vector>

#include "constants.hpp"
#include "file_read.hpp"
#include "runtime_variables.hpp"
#include "energy_grid.hpp"

class DistData {
    public:
        int za;
        int mat;
        double temp;
        double t_eff;
        double temp_ratio;
        double a0;
        double e_max;
        double m0;
        double free_xs;
        double bound_xs;

        std::vector<double> alphas;
        std::vector<double> betas;
        std::vector<double> half_betas;
        std::vector<std::vector<double>> tsl_vals;

        std::vector<double> inc_energy_grid;
        std::vector<double> ii_xs;
        std::vector<std::vector<double>> beta_vals;
        std::vector<std::vector<double>> beta_pdfs;
        std::vector<std::vector<double>> beta_cdfs;
        std::vector<double> beta_cdf_grid;
        std::vector<std::vector<double>> fit_beta_vals;

        std::vector<double> beta_grid;
        std::vector<std::vector<double>> alpha_vals;
        std::vector<std::vector<double>> alpha_pdfs;
        std::vector<std::vector<double>> alpha_cdfs;
        std::vector<double> alpha_cdf_grid;
        std::vector<std::vector<double>> fit_alpha_vals;

        // Constructor
        DistData(TslFileData& file_data);

        // Public facing methods
        double return_sym_SCT(double const& alpha, double const& beta);
        double return_asym_SCT(double const& alpha, double const& beta);
        double return_asym_SCT_alpha_integral(double const& alpha_l, double const& alpha_u, double const& beta);
        std::pair<double, bool> return_arbitrary_TSL_val(double const& alpha, double const& beta);
        std::pair<std::vector<double>, std::vector<double>> return_beta_pdf(double const& inc_energy);
        std::pair<std::vector<double>, std::vector<double>> return_linearized_beta_pdf(double const& inc_energy);
        double return_ii_xs_value(double const& inc_energy);
        std::vector<double> return_ii_xs_vector(std::vector<double> const& inc_energies);
        std::pair<std::vector<double>, std::vector<double>> return_linearized_ii_xs();
        std::pair<std::vector<double>, std::vector<double>> return_final_ii_xs();
        std::pair<std::vector<double>, std::vector<double>> return_linearized_alpha_pdf(double const& beta);
        void calculate_sampling_dists();

    private:
        double __inc_ener_hold__;
        double __beta_hold__;

        double __asym_SCT_alpha_integral_bounds__(double const& alpha, double const& beta);
        double __calculate_beta_min__(double const& inc_energy);
        double __calculate_beta_max__(double const& inc_energy);
        std::pair<double, double> __calculate_alpha_extrema__(double const& inc_energy, double const& beta);

        std::vector<double> __get_viable_alphas__(double const& inc_energy, double const& beta);
        std::vector<double> __get_viable_betas__(double const& inc_energy);
        std::pair<std::vector<double>, std::vector<bool>> __get_alpha_line__(std::vector<double> const& alpha_vals, double const& beta);
        double __integrate_alpha_line__(std::vector<double> const& alpha_vals, std::vector<double> const& vals, std::vector<bool> const& truthy, double const& beta);
        double __get_beta_pdf_val__(double const& inc_energy, double const& beta);
        double __wrapper_get_beta_pdf_val__(double const& beta);

        double __wrapper_get_alpha_pdf_val__(double const& alpha);

        void __get_beta_sampling_dists__();
        void __get_alpha_sampling_dists__();
};

// Function calls
void process_file(const std::string& file_path, const std::string& output_file);
void print_array(std::vector<double> array);

#endif