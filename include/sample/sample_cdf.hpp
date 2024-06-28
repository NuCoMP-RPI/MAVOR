#ifndef MAVOR_SAMPLE_SAMPLE_CDF_H
#define MAVOR_SAMPLE_SAMPLE_CDF_H

#include <iostream>
#include <vector>

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

        std::vector<double> ii_xs;
        std::vector<double> inc_ener_grid;
        std::vector<double> beta_cdf_grid;
        std::vector<double> fit_betas;

        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;
        std::vector<double> fit_alphas;

        // Constructor
        CDFFile(std::string const & file_path);

        // Public Methods
    private:
};

void sample_cdf();

#endif