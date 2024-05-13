#ifndef MAVOR_FILE_READ_H
#define MAVOR_FILE_READ_H

#include <iostream>
#include <vector>

#include "H5Cpp.h"

#include "constants.hpp"

class TslFileData {
    public:
        int lat;
        int lasym;
        int lln;
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
        std::vector<double> tsl_vals_array;
        std::vector<std::vector<double>> tsl_vals;

        // Constructor to read in the data from the HDF5 file
        TslFileData(const std::string& file_path);

        // Public facing methods to return desired versions of the TSL data
        std::vector<double> return_scaled_alphas(double const & ref_temp = ref_temp_k);
        std::vector<double> return_betas();
        std::vector<double> return_scaled_betas(double const & ref_temp = ref_temp_k);
        std::vector<double> return_full_betas();
        std::vector<double> return_full_scaled_betas(double const & ref_temp = ref_temp_k);
        std::vector<std::vector<double>> return_tsl_vals();
        std::vector<std::vector<double>> return_half_sym_tsl_vals();
        std::vector<std::vector<double>> return_half_asym_tsl_vals();
        std::vector<std::vector<double>> return_full_sym_tsl_vals();
        std::vector<std::vector<double>> return_full_asym_tsl_vals();

    private:
        // Private methods to handle the TSL data
        void __matrix_element_exp__(std::vector<std::vector<double>>&matrix);
        void __vec_element_mult__(std::vector<double>&vec, double const val);
        std::vector<std::vector<double>> __vector_to_matrix__(std::vector<double> const & flat_vector, int const n_rows, int const n_cols);
        std::vector<double> __vector_mirror__(std::vector<double> const & arr, bool const del_duplicate);
        std::vector<double> __negative_vector_mirror__(std::vector<double> const & arr, bool const del_duplicate);
        std::vector<std::vector<double>> __matrix_2d_mirror__(std::vector<std::vector<double>> const & matrix2d, bool const del_duplicate);
        std::vector<double> __lat_scale__(std::vector<double> const & arr, double const ref_temp = ref_temp_k);
};
#endif