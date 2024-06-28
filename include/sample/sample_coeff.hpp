#ifndef MAVOR_SAMPLE_SAMPLE_COEFF_H
#define MAVOR_SAMPLE_SAMPLE_COEFF_H

#include <iostream>
#include <vector>

#include "predefined_fit_settings.hpp"

class CoeffFile{
    public:
        // Variables
        int za;
        int mat;
        double a0;
        double e_max;
        double m0;
        double free_xs;
        double bound_xs;

        double minimum_temperature;
        double maximum_temperature;
        
        bool xs_scale_temperatures;
        double xs_scale_minimum;
        double xs_scale_maximum;
        std::string xs_basis_function_string;
        BasisFunction xs_basis_function;

        bool beta_scale_temperatures;
        double beta_scale_minimum;
        double beta_scale_maximum;
        std::string beta_basis_function_string;
        BasisFunction beta_basis_function;
        
        bool alpha_scale_temperatures;
        double alpha_scale_minimum;
        double alpha_scale_maximum;
        std::string alpha_basis_function_string;
        BasisFunction alpha_basis_function;

        std::vector<double> inc_ener_grid;
        std::vector<double> beta_cdf_grid;
        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;

        std::vector<double> ii_xs_coeffs;
        std::vector<double> beta_coeffs;
        std::vector<double> alpha_coeffs;
        // Constructor
        CoeffFile(std::string const & file_path);

        // Public Methods
    private:

        void set_basis_function__(BasisFunction & basis_func, std::string const& basis_func_string);
};

void sample_coeff();

#endif