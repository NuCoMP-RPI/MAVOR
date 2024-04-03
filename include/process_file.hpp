#ifndef MAVOR_PROCESS_FILE_H 
#define MAVOR_PROCESS_FILE_H 

#include <iostream>
#include <vector>

#include "constants.hpp"
#include "file_read.hpp"

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
        std::vector<std::vector<double>> tsl_vals;

        // Constructor
        DistData(TslFileData& file_data);

        // Public facing methods
        double return_sym_SCT(double const& alpha, double const& beta);
        double return_asym_SCT(double const& alpha, double const& beta);
        double return_asym_SCT_alpha_integral(double const& alpha_l, double const& alpha_u, double const& beta);
        std::pair<double, bool> return_arbitrary_TSL_val(double const& alpha, double const& beta);
        std::pair<std::vector<double>, std::vector<double>> return_beta_pdf(double const& inc_energy);
        double return_incoherent_inelastic_xs(double const& inc_energy);

    private:
        double __asym_SCT_alpha_integral_bounds__(double const& alpha, double const& beta);
        double __calculate_beta_min__(double const& inc_energy);
        double __calculate_beta_max__(double const& inc_energy);
        std::pair<double, double> __calculate_alpha_extrema__(double const& inc_energy, double const& beta);

        std::vector<double> __get_viable_alphas__(double const& inc_energy, double const& beta);
        std::vector<double> __get_viable_betas__(double const& inc_energy);
        std::pair<std::vector<double>, std::vector<bool>> __get_alpha_line__(std::vector<double> const& alpha_vals, double const& beta);
        double __integrate_alpha_line__(std::vector<double> const& alpha_vals, std::vector<double> const& vals, std::vector<bool> const& truthy, double const& beta);
        double __get_beta_pdf_val(double const& inc_energy, double const& beta);
};

// Function calls
void process_file(const std::string& file_path);
void print_array(std::vector<double> array);

#endif