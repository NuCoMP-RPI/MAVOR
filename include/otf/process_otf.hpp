#ifndef MAVOR_PROCESS_OTF_H
#define MAVOR_PROCESS_OTF_H

#include <iostream>
#include <vector>

class OTFData{
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
        std::vector<std::vector<std::vector<double>>> fit_beta_vals;

        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;
        std::vector<std::vector<std::vector<double>>> fit_alpha_vals;

        // Constructor
        OTFData(const std::string & directory);

    private:

};

#endif