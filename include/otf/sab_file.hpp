#ifndef MAVOR_SAB_FILE_H
#define MAVOR_SAB_FILE_H

#include <iostream>
#include <vector>

/// @brief Class to store and process SAB sampling distributions
class SabData{
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

        std::vector<double> inc_energy_grid;
        std::vector<double> ii_xs;
        std::vector<double> beta_cdf_grid;
        std::vector<std::vector<double>> beta_vals;

        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;
        std::vector<std::vector<double>> alpha_vals;

        /// @brief Constructor that initializes SAB data by reading an HDF5 file.
        /// @param file_path Path to the HDF5 file containing SAB data.
        SabData(const std::string& file_path);
};

#endif