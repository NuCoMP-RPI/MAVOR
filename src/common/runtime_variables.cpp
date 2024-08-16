#include <iostream>

#include "runtime_variables.hpp"

// Control variables for main program

bool silence = false;
bool verbose = false;
bool log_run = false;

// NJOY subcommand variables



// SAB subcommand variables 

int beta_integration_scheme = 2;
int beta_interpolation_scheme = 2;
int alpha_integration_scheme = 2;
int alpha_interpolation_scheme = 2;

int num_beta_cdf_points = 100;
int beta_cdf_extent = 10;
int num_alpha_cdf_points = 100;
int alpha_cdf_extent = 10;

std::string sab_input_file = "test_files/HinYH2_293K_tsl.h5";
std::string sab_output_file = "CDF_distributions.h5";

bool use_external_energy_grid = false;
std::string energy_grid_loc;
bool use_internal_energy_grid = false;
int predefined_energy_grid_key;

double beta_max = 50;
double sct_cutoff = 1.9219477278e-98;  // Based off the sabmin value in thermr | sabmin = exp(-225) | Found line 1609 and 1628 of thermr.f90
double alpha_min = 1e-10;
double e_min = 1e-5;
int num_energies = 105;

// OTF subcommand variables

std::string otf_input_directory = "/home/blakec4/extra_space/My_Programs/test_Mavor/Unioned_Results/HinYH2";
std::string otf_output_file = "OTF_Coefficients.h5";

int fit_group = 0;

bool basic_xs_fit_override = false;
bool basic_beta_fit_override = false;
bool basic_alpha_fit_override = false;
bool full_xs_fit_override = false;
bool full_beta_fit_override = false;
bool full_alpha_fit_override = false;

int user_predefined_xs_fit = 0;
int user_predefined_xs_num_coeffs = 5;
int user_predefined_beta_fit = 0;
int user_predefined_beta_num_coeffs = 5;
int user_predefined_alpha_fit = 0;
int user_predefined_alpha_num_coeffs = 5;

// These defaults don't mean anything and should be overwritten later when processing
int xs_num_coeffs = 5;
bool xs_scale_temp = true;
double xs_temp_scale_min = -1;
double xs_temp_scale_max = 1;
int xs_basis_function = 10;
bool xs_override_num_coeffs = false;
bool xs_override_scale_temp = false;
bool xs_override_temp_scale_min = false;
bool xs_override_temp_scale_max = false;
bool xs_override_fit_function = false;

// These defaults don't mean anything and should be overwritten later when processing
int beta_num_coeffs = 5;
bool beta_scale_temp = true;
double beta_temp_scale_min = -1;
double beta_temp_scale_max = 1;
int beta_basis_function = 10;
bool beta_override_num_coeffs = false;
bool beta_override_scale_temp = false;
bool beta_override_temp_scale_min = false;
bool beta_override_temp_scale_max = false;
bool beta_override_fit_function = false;

// These defaults don't mean anything and should be overwritten later when processing
int alpha_num_coeffs = 5;
bool alpha_scale_temp = true;
double alpha_temp_scale_min = -1;
double alpha_temp_scale_max = 1;
int alpha_basis_function = 10;
bool alpha_override_num_coeffs = false;
bool alpha_override_scale_temp = false;
bool alpha_override_temp_scale_min = false;
bool alpha_override_temp_scale_max = false;
bool alpha_override_fit_function = false;

// sample subcommand variables

std::string sample_input_file = "";
std::string sample_cdf_test_file = "test_files/HinYH2_293K_CDFs.h5";
std::string sample_coeff_test_file = "test_files/HinYH2_coeffs.h5";
std::string sample_output_file = "Sampling_results.h5";
bool sample_cdf_file = false;
bool sample_coeff_file = false;

double sample_incident_energy = 0.01;
double sample_temperature = 400;
int sample_num_samples = static_cast<int>(1e6);
unsigned int sample_seed = 856526177;