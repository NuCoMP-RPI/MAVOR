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
std::string input_file = "test_inputs/HinYH2_293K.h5";
std::string output_file = "Results.h5";