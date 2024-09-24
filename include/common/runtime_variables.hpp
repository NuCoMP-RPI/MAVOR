#ifndef MAVOR_RUNTIME_VARIABLES_H
#define MAVOR_RUNTIME_VARIABLES_H

#include <iostream>
#include <vector>
#include <map>

// Control variables for the main program

extern bool silence;
extern bool verbose;
extern bool log_run;

// NJOY subcommand variables



// Sab subcommand variables

extern int beta_integration_scheme;
extern int beta_interpolation_scheme;
extern int alpha_integration_scheme;
extern int alpha_interpolation_scheme;

extern int num_beta_cdf_points;
extern int beta_cdf_extent;
extern int num_alpha_cdf_points;
extern int alpha_cdf_extent;

extern std::string sab_input_file;
extern std::string sab_output_file; 

extern bool use_external_energy_grid;
extern std::string energy_grid_loc;
extern bool use_internal_energy_grid;
extern int predefined_energy_grid_key;

extern double beta_max;
extern double sct_cutoff;
extern double alpha_min;
extern double e_min;
extern int num_energies;
    
// DIST subcommand for SAB

extern bool override_sab;
extern std::map<int, std::string> distribution_choices;
extern int distribution_choice;
extern double dist_incident_energy;
extern double dist_outgoing_energy;
extern bool convert_to_eemu;

// OTF subcommand variables

extern std::string otf_input_directory;
extern std::string otf_output_file;

extern int fit_group;

extern bool basic_xs_fit_override;
extern bool basic_beta_fit_override;
extern bool basic_alpha_fit_override;
extern bool full_xs_fit_override;
extern bool full_beta_fit_override;
extern bool full_alpha_fit_override;

extern int user_predefined_xs_fit;
extern int user_predefined_xs_num_coeffs;
extern int user_predefined_beta_fit;
extern int user_predefined_beta_num_coeffs;
extern int user_predefined_alpha_fit;
extern int user_predefined_alpha_num_coeffs;

extern int xs_num_coeffs;
extern bool xs_scale_temp;
extern double xs_temp_scale_min;
extern double xs_temp_scale_max;
extern int xs_basis_function;
extern bool xs_override_num_coeffs;
extern bool xs_override_scale_temp;
extern bool xs_override_temp_scale_min;
extern bool xs_override_temp_scale_max;
extern bool xs_override_fit_function;

extern int beta_num_coeffs;
extern bool beta_scale_temp;
extern double beta_temp_scale_min;
extern double beta_temp_scale_max;
extern int beta_basis_function;
extern bool beta_override_num_coeffs;
extern bool beta_override_scale_temp;
extern bool beta_override_temp_scale_min;
extern bool beta_override_temp_scale_max;
extern bool beta_override_fit_function;

extern int alpha_num_coeffs;
extern bool alpha_scale_temp;
extern double alpha_temp_scale_min;
extern double alpha_temp_scale_max;
extern int alpha_basis_function;
extern bool alpha_override_num_coeffs;
extern bool alpha_override_scale_temp;
extern bool alpha_override_temp_scale_min;
extern bool alpha_override_temp_scale_max;
extern bool alpha_override_fit_function;

// sample subcommand variables

extern std::string sample_input_file;
extern std::string sample_cdf_test_file;
extern std::string sample_coeff_test_file;
extern std::string sample_cdf_output_file;
extern std::string sample_coeff_output_file;
extern std::string sample_output_file;
extern bool sample_cdf_file;
extern bool sample_coeff_file;
extern bool sample_only_timing_results;

extern double sample_incident_energy;
extern double sample_temperature;
extern int sample_num_samples;
extern unsigned int sample_seed;

extern bool sample_xs_default_eval;
extern bool sample_xs_naive_eval;
extern bool sample_xs_optimal_eval;
extern bool sample_xs_override_eval;
extern std::string sample_xs_override_evaluation_type;

extern bool sample_beta_default_eval;
extern bool sample_beta_naive_eval;
extern bool sample_beta_optimal_eval;
extern bool sample_beta_override_eval;
extern std::string sample_beta_override_evaluation_type;

extern bool sample_alpha_default_eval;
extern bool sample_alpha_naive_eval;
extern bool sample_alpha_optimal_eval;
extern bool sample_alpha_override_eval;
extern std::string sample_alpha_override_evaluation_type;

#endif