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

        // Constructor
        CDFFile(std::string const & file_path);

        // Public Methods
        std::pair<double, double> single_sample(const double & inc_ener, const double & xi_1, const double & xi_2);
        void all_sample(const double & inc_ener);
        void write_results();
    private:
        std::pair<double, double> return_alpha_extrema__(const double & inc_ener, const double & beta);
};

void sample_cdf();

#endif