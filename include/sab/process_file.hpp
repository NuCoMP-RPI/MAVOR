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

        /// Constructor
        /// @brief Constructor to initialize the processing of TSL data
        /// @param file_data TSL data class
        DistData(TslFileData& file_data);

        // Public facing methods

        /// @brief Calculates the symmetric short collision time approximation
        /// @param alpha Alpha value to calculate SCT
        /// @param beta Beta value to calculate SCT
        /// @return Symmetric SCT approximation at alpha and beta
        double return_sym_SCT(double const& alpha, double const& beta);
        
        /// @brief Calculates the asymmetric short collision time approximation
        /// @param alpha Alpha value to calculate SCT
        /// @param beta Beta value to calculate SCT
        /// @return Asymmetric SCT approximation at alpha and beta
        double return_asym_SCT(double const& alpha, double const& beta);
        
        /// @brief Calculated the definte integral of the asymmetric short collision time approximation at a given beta between two alpha points
        /// @param alpha_l Lower alpha bound
        /// @param alpha_u Upper alpha bound
        /// @param beta Beta value to calculate integral
        /// @return Integral of the asymmetric SCT approximation
        double return_asym_SCT_alpha_integral(double const& alpha_l, double const& alpha_u, double const& beta);
        
        /// @brief Calculates an arbitrary TSL value given the TSL data
        /// @param alpha Desired alpha value
        /// @param beta Desired beta value
        /// @return Desired TSL value
        std::pair<double, bool> return_arbitrary_TSL_val(double const& alpha, double const& beta);
        
        /// @brief Calculates the beta PDF given an incident energy
        /// @param inc_energy Desired incident energy in eV
        /// @return (first) Beta values, (second) PDF values
        std::pair<std::vector<double>, std::vector<double>> return_beta_pdf(double const& inc_energy);
        
        /// @brief Calculates the beta PDF given an incident energy and then preforms the linearization process.
        /// @param inc_energy Desired incident energy in eV
        /// @return (first) Beta values, (second) PDF values
        std::pair<std::vector<double>, std::vector<double>> return_linearized_beta_pdf(double const& inc_energy);
        
        /// @brief Calculates the XS value given an incident energy
        /// @param inc_energy Desired incident energy in eV
        /// @return XS value in barns
        double return_ii_xs_value(double const& inc_energy);
        
        /// @brief Calculates the XS values given a vector of incident energies
        /// @param inc_energies Desired incident energies in eV
        /// @return XS values in barns
        std::vector<double> return_ii_xs_vector(std::vector<double> const& inc_energies);
        
        /// @brief Calculates the XS values at 100 logrithmically spaced points from the minimum incident energy 
        /// (set by command line argument) to the maximum incident energy (as defined in the ENDF file for the material).
        /// @return (first) incident energies in eV, (second) XS values in barns
        std::pair<std::vector<double>, std::vector<double>> return_linearized_ii_xs();
        
        /// @brief Calculates the XS at the given incident energies set by command line argument or linearizes the XS values
        /// @return (first) incident energies in eV, (second) XS values in barns
        std::pair<std::vector<double>, std::vector<double>> return_final_ii_xs();
        
        /// @brief Calculates the alpha PDF given the desired beta value and then applies the linearization process.  
        /// This function does not consider the incident energy and is therefore calculated over all alpha values
        /// @param beta Desired beta value
        /// @return (first) Alpha values, (second) PDF values
        std::pair<std::vector<double>, std::vector<double>> return_linearized_alpha_pdf(double const& beta);
        
        /// @brief Calculates the alpha PDF at the allowable alphas given a desired incident energy and beta value
        /// @param inc_energy Desired incident energy in eV
        /// @param beta Desired beta value
        /// @return (first) Alpha values, (second) PDF values
        std::pair<std::vector<double>, std::vector<double>> return_viable_linearized_alpha_pdf(double const& inc_energy, double const& beta);
        
        /// @brief Runner function that calulates the sampling distributions and then stores them in the class
        void calculate_sampling_dists();
        
        /// @brief Converts a beta value into the associated outgoing energy in eV
        /// @param inc_energy Desired incident energy in eV
        /// @param beta Desired beta value
        /// @return Outgoing energy in eV
        double beta_to_outgoing_energy(double const& inc_energy, double const& beta);
        
        /// @brief Converts a vector of beta values into outgoing energies
        /// @param inc_energy Desired incident energy in eV
        /// @param betas Desired beta values
        /// @return Outgoing energies in eV
        std::vector<double> betas_to_outgoing_energies(double const& inc_energy, std::vector<double> const& betas);
        
        /// @brief Calculates a beta value given an incident and outgoing energy
        /// @param inc_energy Incident energy in eV
        /// @param out_energy Outgoing energy in eV
        /// @return Beta value
        double return_beta(double const& inc_energy, double const& out_energy);
        
        /// @brief Calculates the scattering angle given an incident and outgoing energy and alpha value
        /// @param inc_energy Desired incident energy in eV
        /// @param out_energy Desired outgoing energy in eV
        /// @param alpha Desired alpha value
        /// @return Scattering angles
        double alpha_to_scattering_angle(double const& inc_energy, double const& out_energy, double const& alpha);
        
        /// @brief Calculates teh scattering angles given an incident and outgoing energy and a vector of alpha values
        /// @param inc_energy Desired incident energy in eV
        /// @param out_energy Desired outgoing energy in eV
        /// @param alphas Desried alpha values
        /// @return Scattering angles 
        std::vector<double> alphas_to_scatting_angles(double const& inc_energy, double const& out_energy, std::vector<double> const& alphas);

    private:
        /// @brief A working variable to hold the incident energy in the linearization process
        double inc_ener_hold__;
        
        /// @brief A working variable to hold the beta value in the linearization process
        double beta_hold__;

        /// @brief Calculates the asymmetric short collision time integral bound given an alpha and beta value
        /// @param alpha Desired alpha value
        /// @param beta Desired beta value
        /// @return Integral bound
        double asym_SCT_alpha_integral_bounds__(double const& alpha, double const& beta);
        
        /// @brief Calculates the minimum beta value given an incident energy
        /// @param inc_energy Desired incident energy in eV
        /// @return Minumum beta value
        double calculate_beta_min__(double const& inc_energy);
        
        /// @brief Calculates teh maximum beta value given an incident energy.
        /// Currently only returns the value set in runtime variables
        /// @param inc_energy Desried incident energy in eV
        /// @return Maximum beta value
        double calculate_beta_max__(double const& inc_energy);
        
        /// @brief Calculates the minimum and maximum alpha values given an incident energy and beta value.
        /// @param inc_energy Desired incident energy in eV
        /// @param beta Deisred beta value
        /// @return Minimum and maxiumum alpha values, respectively
        std::pair<double, double> calculate_alpha_extrema__(double const& inc_energy, double const& beta);

        /// @brief Returns a vector of stored alpha values that are within the alpha extrema and adds the extrema if not already present
        /// @param inc_energy Desried incident energy in eV
        /// @param beta Desired beta value
        /// @return Viable alpha values
        std::vector<double> get_viable_alphas__(double const& inc_energy, double const& beta);
        
        /// @brief Returns a vector of stored beta values that are within the alpha beta extrema and adds teh extrema if not already present
        /// @param inc_energy Desired incident energy in eV
        /// @return Viable beta values
        std::vector<double> get_viable_betas__(double const& inc_energy);
        
        /// @brief Returns or calulates the TSL values at the given alpha points and indicates whether the SCT was used to calculate a point
        /// @param alpha_vals Desired alpha values to calculate the TSL values
        /// @param beta Desired beta value
        /// @return (first) TSL values, (second) Was SCT time used
        std::pair<std::vector<double>, std::vector<bool>> get_alpha_line__(std::vector<double> const& alpha_vals, double const& beta);
        
        /// @brief Analytically integrates an alpha line
        /// @param alpha_vals Alpha values
        /// @param vals TSL values corresponding to the alpha_vals
        /// @param truthy Indication if SCT was used to calculate a TSL value
        /// @param beta Desired beta value
        /// @return Value of the integral
        double integrate_alpha_line__(std::vector<double> const& alpha_vals, std::vector<double> const& vals, std::vector<bool> const& truthy, double const& beta);
        
        /// @brief Calculates a PDF values corresponding the a certain beta value
        /// @param inc_energy Desired incident energy in eV
        /// @param beta Desired beta value
        /// @return PDF value
        double get_beta_pdf_val__(double const& inc_energy, double const& beta);
        
        /// @brief Wrapper to get a PDF value for a desired beta using the "inc_ener_hold__" variable.
        /// Used in the linearization process
        /// @param beta Desired beta value
        /// @return PDF value
        double wrapper_get_beta_pdf_val__(double const& beta);

        /// @brief Wrapper to get a PDF value for a desired alpha using the "beta_hold__" variable.
        /// Used in the linearization process
        /// @param alpha Desired alpha value
        /// @return PDF value
        double wrapper_get_alpha_pdf_val__(double const& alpha);

        /// @brief Runner function to calculate the beta sampling distributions
        void get_beta_sampling_dists__();
        
        /// @brief Runner function to calculate the alpha sampling distributions
        void get_alpha_sampling_dists__();
};
#endif