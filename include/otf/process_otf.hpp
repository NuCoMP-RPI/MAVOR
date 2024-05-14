#ifndef MAVOR_PROCESS_OTF_H
#define MAVOR_PROCESS_OTF_H

#include "Eigen/Dense"

#include <iostream>
#include <vector>

class OTFData{
    public:
        // Variables 
        int za;
        int mat;
        double a0;
        double e_max;
        double m0;
        double free_xs;
        double bound_xs;

        std::vector<double> temps;

        std::vector<double> inc_energy_grid;
        // order is <inc_ene, temp>
        std::vector<Eigen::VectorXd> ii_xs;
        std::vector<double> beta_cdf_grid;
        // order is <inc_ene, b_cdf, temp>
        std::vector<std::vector<Eigen::VectorXd>> fit_beta_vals;

        std::vector<double> beta_grid;
        std::vector<double> alpha_cdf_grid;
        //order is <beta, a_cdf, temp>
        std::vector<std::vector<Eigen::VectorXd>> fit_alpha_vals;

        // Constructor
        OTFData(const std::string & directory);

        void generate_coefficients();

    private:
        template<typename T> void __check__(T const & val_1, T const & val_2, std::string const item_name);
        void __generate_A_matrix__();

};

#endif