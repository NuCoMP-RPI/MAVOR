#ifndef MAVOR_SAMPLE_SAMPLE_COEFF_H
#define MAVOR_SAMPLE_SAMPLE_COEFF_H

#include <iostream>
#include <vector>

#include "predefined_coeff_evaluations.hpp"


/// @brief Class to read in coefficient sampling data, perform the sampling, and then write the results
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

        double time_to_sample_ms;
        
        bool xs_scale_temperatures;
        double xs_scale_minimum;
        double xs_scale_maximum;
        std::string xs_basis_function_string;
        EvaluationFunction xs_eval_func;

        bool beta_scale_temperatures;
        double beta_scale_minimum;
        double beta_scale_maximum;
        std::string beta_basis_function_string;
        EvaluationFunction beta_eval_func;
        
        bool alpha_scale_temperatures;
        double alpha_scale_minimum;
        double alpha_scale_maximum;
        std::string alpha_basis_function_string;
        EvaluationFunction alpha_eval_func;

        std::vector<double> inc_ener_grid;
        std::vector<double> beta_cdf_grid;
        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;

        std::vector<double> ii_xs_coeffs;
        int num_xs_coeffs;
        std::vector<double> beta_coeffs;
        int num_beta_coeffs;
        std::vector<double> alpha_coeffs;
        int num_alpha_coeffs;

        std::vector<double> xi_1;
        std::vector<double> xi_2;

        std::vector<double> sampled_secondary_energies;
        std::vector<double> sampled_scattering_cosines;

        /// Constructor
        /// @brief Constructor to initialize the coefficient sampling data.
        /// @param file_path Path to the coefficient file to be read in.
        CoeffFile(std::string const & file_path);

        /// @brief Performs a single random sample of the coefficient data.
        /// @param temp Temperature to perform the sample
        /// @param inc_ener Incident energy of the neutron 
        /// @param xi_1 First random variable to sample energy
        /// @param xi_2 Second random variable to sample scattering cosine
        /// @return std::pair<double, double> containing the sampled energy and scattering cosine
        std::pair<double, double> single_sample(const double & temp, const double & inc_ener, const double & xi_1, const double & xi_2);

        /// @brief Performs sampling over two random variable vectors that are already initalized and writes results into class vectors
        /// @param inc_ener Incident energy of the neutron
        void all_sample(const double & inc_ener);

        /// @brief Writes the results of the sampling to an HDF5 file
        void write_results();

    private:
        /// @brief Sets the evaluation function for the coefficients
        /// @param eval_func Struct that contains a pointer to the evaluation function
        /// @param basis_func_string String of the basis function used to generate the coefficients
        void set_eval_function__(EvaluationFunction &eval_func, std::string const &basis_func_string);

        /// @brief Calculates the alpha extrema
        /// @param temp Temperature to perform the sample
        /// @param inc_ener Incident energy of the neutron  
        /// @param beta Sampled beta value
        /// @return Extrema alpha values
        std::pair<double, double> return_alpha_extrema__(const double & temp, const double & inc_ener, const double & beta);

        /// @brief Samples a beta value
        /// @param temp Temperature to perform the sample
        /// @param inc_ener Incident energy of the neutron 
        /// @param xi Random value
        /// @return Sampled beta value
        double sample_beta__(const double & temp, const double & inc_ener, const double & xi);

        /// @brief Converts the sampled beta value into scattering energy
        /// @param temp Temperature to perform the sample
        /// @param inc_ener Incident energy of the neutron 
        /// @param beta Sampled beta value
        /// @return Secondary energy
        double calculate_secondary_energy__(const double & temp, const double & inc_ener, const double & beta);

        /// @brief Samples an alpha value
        /// @param temp Temperature to perform the sample
        /// @param inc_ener Incident energy of the neutron 
        /// @param beta Sampled beta value
        /// @param xi Random value
        /// @return Sampled alpha value
        double sample_alpha__(const double & temp, const double & inc_ener, const double & beta, const double & xi);

        /// @brief Samples the an alpha that corresponds to the a bracketing beta index.
        /// @param temp Temperature to perform the sample
        /// @param beta_ind Index of the beta grid to sample along
        /// @param alpha_extrema Results of the "return_alpha_extrema__" function.  Indicated the sampling bounds for alpha
        /// @param xi Random variable
        /// @param evaled_basis_points Evaluated orders of the basis function that need to be multiplied and summed over the coefficients
        /// @return Sampled alpha given a beta line
        double sample_bounding_alpha__(const double & temp, const int & beta_ind, const std::pair<double, double> & alpha_extrema, const double & xi, const std::vector<double> &evaled_basis_points);
        
        /// @brief Converts the sampled alpha value to scattering cosine
        /// @param temp Temperature to perform the sample
        /// @param inc_ener Incident energy of the neutron 
        /// @param sec_ener Secondary energy of the neutron
        /// @param alpha Sampled alpha value
        /// @return Scattering cosine
        double calculate_scattering_cosine__(const double & temp, const double & inc_ener, const double & sec_ener, const double & alpha);
};

void sample_coeff();

#endif