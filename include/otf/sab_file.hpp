#ifndef MAVOR_SAB_FILE_H
#define MAVOR_SAB_FILE_H

#include <iostream>
#include <vector>

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

        // Constructor
        SabData(const std::string& file_path);

    private:
        std::vector<std::vector<double>> __vector_to_matrix__(std::vector<double> const & flat_vec, int const n_rows, int const n_cols);

};

#endif