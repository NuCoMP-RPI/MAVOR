#include <iostream>

#include "runtime_variables.hpp"

// Control variables for main program

bool silence = false;
bool verbose = false;
bool log_run = false;

// NJOY subcommand variables

bool force_run = false;
std::string tsl_leapr_file = std::string(BUILD_DIR) + "/test_files/tsl-HinYH2.leapr";
std::string tsl_leapr_write_dir = std::string(BUILD_DIR) + "/leapr_files";
std::string tsl_njoy_results_dir = std::string(BUILD_DIR) + "/njoy_results";
bool tsl_leapr_use_temp_delta = false;
bool tsl_leapr_use_num_temps = false;
std::vector<double> tsl_leapr_temps;
double tsl_leapr_delta_temp = 5;
int tsl_leapr_num_temps = 5;

std::string tsl_njoy_exe_loc = TSL_NJOY_EXE_LOC;
std::string tsl_njoy_sim_loc = std::string(BUILD_DIR) + "/njoy_sims";

// SAB subcommand variables 

int beta_integration_scheme = 2;
int beta_interpolation_scheme = 2;
int alpha_integration_scheme = 2;
int alpha_interpolation_scheme = 2;

bool linearize_cdfs = false;

bool use_sigmoid_cdfs = true;
int num_beta_cdf_points = 400;
int beta_cdf_extent = 7;
int num_alpha_cdf_points = 400;
int alpha_cdf_extent = 7;

bool use_external_cdfs = false;
std::string alpha_cdf_grid_loc;
std::string beta_cdf_grid_loc;

std::string sab_input_file = std::string(BUILD_DIR) + "/test_files/HinYH2_tsl.h5";
std::string sab_output_file = std::string(BUILD_DIR) + "/CDF_distributions.h5";

bool use_external_energy_grid = false;
std::string energy_grid_loc;
bool use_internal_energy_grid = false;
int predefined_energy_grid_key;

double beta_max = 50;
double sct_cutoff = 1.9219477278e-98;  // Based off the sabmin value in thermr | sabmin = exp(-225) | Found line 1609 and 1628 of thermr.f90
double alpha_min = 1e-10;
double e_min = 1e-5;
int num_energies = 105;

// DIST subcommand for SAB

bool override_sab = false;
std::map<int, std::string> distribution_choices = 
    {
        {1, "Cross-Section"},
        {2, "Outgoing Energy"},
        {3, "Scattering Angle"}
    };
// std::vector<int> distribution_choices_keys = {1,2,3};
int distribution_choice = -1;
double dist_incident_energy = 1;
double dist_outgoing_energy = 0.5;
bool convert_to_eemu = false;

// OTF subcommand variables

std::string otf_input_directory = "/home/blakec4/extra_space/My_Programs/test_Mavor/Unioned_Results/HinYH2";
std::string otf_output_file = std::string(BUILD_DIR) + "/OTF_Coefficients.h5";

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
std::string sample_cdf_test_file = std::string(BUILD_DIR) + "/test_files/HinYH2_cdfs.h5";
std::string sample_coeff_test_file = std::string(BUILD_DIR) + "/test_files/HinYH2_coeffs.h5";
std::string sample_cdf_output_file = std::string(BUILD_DIR) + "/CDF_sampling_results.h5";
std::string sample_coeff_output_file = std::string(BUILD_DIR) + "/COEFF_sampling_results.h5";
std::string sample_output_file = "";
bool sample_cdf_file = false;
bool sample_coeff_file = false;
bool sample_only_timing_results = false;

double sample_incident_energy = 0.01;
double sample_temperature = 400;
int sample_num_samples = static_cast<int>(1e6);
unsigned int sample_seed = 856526177;

bool sample_xs_default_eval = true; // see sample_coeff.cpp for the default behavior, this is just a flag
bool sample_xs_naive_eval = false;
bool sample_xs_optimal_eval = false;
bool sample_xs_override_eval = false;
std::string sample_xs_override_evaluation_type = "";

bool sample_beta_default_eval = true; // see sample_coeff.cpp for the default behavior, this is just a flag
bool sample_beta_naive_eval = false;
bool sample_beta_optimal_eval = false;
bool sample_beta_override_eval = false;
std::string sample_beta_override_evaluation_type = "";

bool sample_alpha_default_eval = true; // see sample_coeff.cpp for the default behavior, this is just a flag
bool sample_alpha_naive_eval = false;
bool sample_alpha_optimal_eval = false;
bool sample_alpha_override_eval = false;
std::string sample_alpha_override_evaluation_type = "";

// elastic subcommand variables

std::string elastic_otf_file = std::string(BUILD_DIR) + "/test_files/HinYH2_coeffs.h5";
std::string elastic_endf_file = std::string(BUILD_DIR) + "/test_files/tsl-HinYH2.endf";
std::string elastic_full_otf_file = std::string(BUILD_DIR) + "/Full_OTF.h5";