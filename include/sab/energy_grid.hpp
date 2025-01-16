#ifndef MAVOR_ENERGY_GRID_H
#define MAVOR_ENERGY_GRID_H

#include <iostream>
#include <vector>

/// @brief Returns the incident energy grid to be used when calculating cross-section and beta distributions.
/// Generates or reads the grid based off of command line arguments
/// @return Incident energy grid
std::vector<double> return_incident_energy_grid();

#endif