#ifndef MAVOR_PROCESS_OTF_H
#define MAVOR_PROCESS_OTF_H

#include "Eigen/Dense"

#include <iostream>
#include <vector>

#include "predefined_fit_settings.hpp"

/// @class OTFData
/// @brief Handles on-the-fly data processing for thermal scattering.
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
        AlphaFit class_alpha_fit;
        BetaFit class_beta_fit;
        XSFit class_xs_fit;

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
        /// @brief Constructs the OTFData object and loads material data from files.
        /// @param directory Path to the directory containing material data files.
        OTFData(const std::string & directory);

        /// @brief Generates coefficients for data fitting.
        void generate_coefficients();

        /// @brief Writes generated coefficients to files.
        void write_coefficients();

    private:
        /// @brief Loads material fit settings from configuration.
        void load_material_fits__();
        
        /// @brief Loads default fit settings when no configuration is provided.
        void load_default_fits__();
        
        /// @brief Overrides fit settings based on command line arguments
        void override_fit_settings__();
        
        /// @brief Checks if two items are equal
        /// @tparam T Type
        /// @param val_1 Value 1 
        /// @param val_2 Value 2
        /// @param item_name Name of the items to check
        /// @throws Runtime Error if the two values are not equal
        template<typename T> void check__(T const & val_1, T const & val_2, std::string const item_name);
        
        /// @brief Generates the A matrix for the solve
        void generate_A_matrices__();
        
        /// @brief Fills the A matrix
        void fill_A_matrices__();
        
        /// @brief Evaluates the fitting function of a certain order at the desired value
        /// @param x Evaluation point
        /// @param number Evaluation order
        /// @param func Fitting function
        /// @return number order of the fitting function evaluated at x
        Eigen::VectorXd eval_fit_func__(double const & x, int const & number, FuncPointer func);
        
        /// @brief Solves the fitting equations to compute coefficients.
        void solve__();
};

#endif