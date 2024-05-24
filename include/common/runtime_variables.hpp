#ifndef MAVOR_RUNTIME_VARIABLES_H
#define MAVOR_RUNTIME_VARIABLES_H

#include <iostream>
#include <vector>

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

// OTF subcommand variables

extern std::string otf_input_directory;
extern std::string otf_output_file;

extern bool xs_fit_override;
extern int xs_num_coeffs;
extern bool xs_scale_temp;
extern double xs_temp_scale_min;
extern double xs_temp_scale_max;
extern int xs_fit_function;

extern bool beta_fit_override;
extern int beta_num_coeffs;
extern bool beta_scale_temp;
extern double beta_temp_scale_min;
extern double beta_temp_scale_max;
extern int beta_fit_function;

extern bool alpha_fit_override;
extern int alpha_num_coeffs;
extern bool alpha_scale_temp;
extern double alpha_temp_scale_min;
extern double alpha_temp_scale_max;
extern int alpha_fit_function;

#endif