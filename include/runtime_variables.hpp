#ifndef MAVOR_RUNTIME_VARIABLES_H
#define MAVOR_RUNTIME_VARIABLES_H

#include <iostream>
#include <vector>

extern int beta_integration_scheme;
extern int beta_interpolation_scheme;
extern int alpha_integration_scheme;
extern int alpha_interpolation_scheme;

extern int num_beta_cdf_points;
extern int beta_cdf_extent;
extern int num_alpha_cdf_points;
extern int alpha_cdf_extent;

extern std::string input_file;
extern std::string output_file; 

extern bool silence;
extern bool verbose;
extern bool log_run;
extern bool no_process;

extern bool use_external_energy_grid;
extern std::string energy_grid_loc;
extern bool use_internal_energy_grid;
extern int predefined_energy_grid_key;

extern std::vector<std::string> known_materials_predefined_energies;

#endif