#ifndef MAVOR_PROCESS_OTF_H
#define MAVOR_PROCESS_OTF_H

#include "Eigen/Dense"

#include <iostream>
#include <vector>

#include "predefined_fit_settings.hpp"

class OTFData{
    public:
        // Variables 
        int za;
        int mat;
        double a0;
        double e_max;
        double m0;
        double free_xs;
        double bound_xs;

        // Fit settings
        int class_xs_num_coeffs;
        bool class_xs_scale_temp;
        double class_xs_temp_scale_min;
        double class_xs_temp_scale_max;
        FitFunction class_xs_fit_function;

        int class_beta_num_coeffs;
        bool class_beta_scale_temp;
        double class_beta_temp_scale_min;
        double class_beta_temp_scale_max;
        FitFunction class_beta_fit_function;

        int class_alpha_num_coeffs;
        bool class_alpha_scale_temp;
        double class_alpha_temp_scale_min;
        double class_alpha_temp_scale_max;
        FitFunction class_alpha_fit_function;

        std::vector<double> temps;
        std::vector<double> xs_temps;
        std::vector<double> beta_temps;
        std::vector<double> alpha_temps;

        std::vector<double> inc_energy_grid;
        // order is <inc_ene, temp>
        std::vector<Eigen::VectorXd> ii_xs;
        std::vector<double> beta_cdf_grid;
        // order is <inc_ene, b_cdf, temp>
        std::vector<std::vector<Eigen::VectorXd>> fit_beta_vals;

        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;
        //order is <beta, a_cdf, temp>
        std::vector<std::vector<Eigen::VectorXd>> fit_alpha_vals;

        Eigen::MatrixXd xs_A;
        Eigen::MatrixXd beta_A;
        Eigen::MatrixXd alpha_A;
        std::vector<Eigen::VectorXd> xs_coeffs;
        std::vector<std::vector<Eigen::VectorXd>> beta_coeffs;
        std::vector<std::vector<Eigen::VectorXd>> alpha_coeffs;

        // Constructor
        OTFData(const std::string & directory);

        void generate_coefficients();

        void write_coefficients();

    private:
        void load_fit_settings__();
        void load_material_fit_settings__(MatPredefinedFitMap::iterator mat_it);
        void load_default_fit_settings__();
        void override_fit_settings__();
        template<typename T> void __check__(T const & val_1, T const & val_2, std::string const item_name);
        void __generate_A_matrices__();
        void __fill_A_matrices__();
        Eigen::VectorXd __eval_fit_func__(double const & x, int const & number, FuncPointer func);
        void __solve__();
};

#endif