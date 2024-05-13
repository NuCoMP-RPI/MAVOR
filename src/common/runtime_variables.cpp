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
std::string sab_input_file = "test_files/HinYH2_293K.h5";
std::string sab_output_file = "Results.h5";

// Just shut it 
bool silence = false;
bool verbose = false;
bool log_run = false;

bool use_external_energy_grid = false;
std::string energy_grid_loc;
bool use_internal_energy_grid = false;
int predefined_energy_grid_key;

double beta_max = 50;
double sct_cutoff = 1.9219477278e-98;  // Based off the sabmin value in thermr | sabmin = exp(-225) | Found line 1609 and 1628 of thermr.f90
double alpha_min = 1e-10;
double e_min = 1e-5;
int num_energies = 105;