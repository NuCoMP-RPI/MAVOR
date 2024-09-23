#ifndef MAVOR_SAMPLE_SAMPLE_COEFF_H
#define MAVOR_SAMPLE_SAMPLE_COEFF_H

#include <iostream>
#include <vector>

#include "predefined_coeff_evaluations.hpp"

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
        double temp;

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
        int num_xs_coeff;
        std::vector<double> beta_coeffs;
        int num_beta_coeffs;
        std::vector<double> alpha_coeffs;
        int num_alpha_coeffs;

        std::vector<double> xi_1;
        std::vector<double> xi_2;

        std::vector<double> sampled_secondary_energies;
        std::vector<double> sampled_scattering_cosines;

        // Constructor
        CoeffFile(std::string const & file_path);

        // Public Methods
        std::pair<double, double> single_sample(const double & inc_ener, const double & xi_1, const double & xi_2);
        void all_sample(const double & inc_ener);
        void write_results();
    private:
        std::pair<double, double> return_alpha_extrema__(const double & inc_ener, const double & beta);
        void set_eval_function_arb__(EvaluationFunction & eval_func, std::string const& basis_func_string, std::string const var_type);
        void set_eval_function__(EvaluationFunction & eval_func, 
                                 std::string const &basis_func_string,
                                 bool const sample_default_eval,
                                 bool const sample_naive_eval,
                                 bool const sample_optimal_eval,
                                 bool const sample_override_eval,
                                 std::string const sample_override_evaluation_type);
};

void sample_coeff();

#endif