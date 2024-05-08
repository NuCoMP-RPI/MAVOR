#include <iostream>

#include "runtime_variables.hpp"

// Define default values

// Integration schemes
int beta_integration_scheme = 2;
int alpha_integration_scheme = 2;

// Interpolation schemes
int beta_interpolation_scheme = 2;
int alpha_interpolation_scheme = 2;

// Beta CDF generation
int num_beta_cdf_points = 400;
int beta_cdf_extent = 10;

// Alpha CDF generation
int num_alpha_cdf_points = 400;
int alpha_cdf_extent = 10;

// Default files
std::string input_file = "test_files/HinYH2_293K.h5";
std::string output_file = "Results.h5";

// Just shut it 
bool silence = false;
bool verbose = false;
bool log_run = false;
bool no_process = false;

bool use_external_energy_grid = false;
std::string energy_grid_loc;
bool use_internal_energy_grid = false;
int predefined_energy_grid_key;