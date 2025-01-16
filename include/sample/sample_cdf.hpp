#ifndef MAVOR_SAMPLE_SAMPLE_CDF_H
#define MAVOR_SAMPLE_SAMPLE_CDF_H

#include <iostream>
#include <vector>

/// @brief Class to read in cdf sampling data, perform the sampling, and then write the results
class CDFFile{
    public:
        // Variables
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

        double time_to_sample_ms;

        std::vector<double> ii_xs;
        std::vector<double> inc_ener_grid;
        std::vector<double> beta_cdf_grid;
        std::vector<double> fit_betas;

        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;
        std::vector<double> fit_alphas;

        std::vector<double> xi_1;
        std::vector<double> xi_2;

        std::vector<double> sampled_secondary_energies;
        std::vector<double> sampled_scattering_cosines;

        /// Constructor
        /// @brief Constructor to initialize the cdf sampling data.
        /// @param file_path Path to the cdf file to be read in.
        CDFFile(std::string const & file_path);

        /// @brief Performs a single random sample of the cdf data.
        /// @param inc_ener Incident energy of the neutron 
        /// @param xi_1 First random variable to sample energy
        /// @param xi_2 Second random variable to sample scattering cosine
        /// @return std::pair<double, double> containing the sampled energy and scattering cosine
        std::pair<double, double> single_sample(const double & inc_ener, const double & xi_1, const double & xi_2);

        /// @brief Performs sampling over two random variable vectors that are already initalized and writes results into class vectors
        /// @param inc_ener Incident energy of the neutron
        void all_sample(const double & inc_ener);

        /// @brief Writes the results of the sampling to an HDF5 file
        void write_results();

    private:

        /// @brief Calculates the alpha extrema
        /// @param inc_ener Incident energy of the neutron  
        /// @param beta Sampled beta value
        /// @return Extrema alpha values
        std::pair<double, double> return_alpha_extrema__(const double & inc_ener, const double & beta);

        /// @brief Samples a beta value
        /// @param inc_ener Incident energy of the neutron 
        /// @param xi Random value
        /// @return Sampled beta value
        double sample_beta__(const double & inc_ener, const double & xi);

        /// @brief Converts the sampled beta value into scattering energy
        /// @param inc_ener Incident energy of the neutron 
        /// @param beta Sampled beta value
        /// @return Secondary energy
        double calculate_secondary_energy__(const double & inc_ener, const double & beta);

        /// @brief Samples an alpha value
        /// @param inc_ener Incident energy of the neutron 
        /// @param beta Sampled beta value
        /// @param xi Random value
        /// @return Sampled alpha value
        double sample_alpha__(const double & inc_ener, const double & beta, const double & xi);

        /// @brief Samples the an alpha that corresponds to the a bracketing beta index.
        /// @param beta_ind Index of the beta grid to sample along
        /// @param alpha_extrema Results of the "return_alpha_extrema__" function.  Indicated the sampling bounds for alpha
        /// @param xi Random variable
        /// @return Sampled alpha given a beta line
        double sample_bounding_alpha__(const int & beta_ind, const std::pair<double, double> & alpha_extrema, const double & xi);

        /// @brief Converts the sampled alpha value to scattering cosine
        /// @param inc_ener Incident energy of the neutron 
        /// @param sec_ener Secondary energy of the neutron
        /// @param alpha Sampled alpha value
        /// @return Scattering cosine
        double calculate_scattering_cosine__(const double & inc_ener, const double & sec_ener, const double & alpha);
};

void sample_cdf();

#endif