#ifndef MAVOR_SAB_FILE_H
#define MAVOR_SAB_FILE_H

#include <iostream>
#include <vector>

/// @brief Class to store and process SAB sampling distriburions
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
        std::vector<std::vector<double>> fit_beta_vals;

        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;
        std::vector<std::vector<double>> fit_alpha_vals;

        /// @brief Constructor that initializes SAB data by reading an HDF5 file.
        /// @param file_path Path to the HDF5 file containing SAB data.
        SabData(const std::string& file_path);

    private:
        /// @brief Converts a flat vector into a 2D matrix.
        /// @param flat_vec The flat vector to convert.
        /// @param n_rows Number of rows in the resulting matrix.
        /// @param n_cols Number of columns in the resulting matrix.
        /// @return A 2D matrix created from the flat vector.
        /// @throws std::domain_error if the size of the flat vector does not match n_rows * n_cols.
        std::vector<std::vector<double>> vector_to_matrix__(std::vector<double> const & flat_vec, int const n_rows, int const n_cols);
};

#endif