#include <iostream>
#include <vector>
#include <fstream>

#include "runtime_variables.hpp"
#include "energy_grid.hpp"
#include "predefined_energy_grids.hpp"
#include "utilities.hpp"
#include "constants.hpp"

std::vector<double> read_energy_file(std::string const & file_path){
    std::vector<double> grid;
    std::fstream file(file_path);
    std::string line;
    while (getline(file, line))
    {
        // right trim the line, should only be one value per line
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        grid.push_back(std::stod(line));
    }
    return grid;
}

std::vector<double> return_incident_energy_grid(double const & e_max){
    if (use_internal_energy_grid){
        auto it = predefined_energy_grids.find(predefined_energy_grid_key);
        if (it != predefined_energy_grids.end()) {
            return it->second;
        } else {
            throw std::domain_error("Selected Material not found.");
        }
    }
    else if (use_external_energy_grid)
    {
        return read_energy_file(energy_grid_loc);
    }
    else {
        return logspace(e_min, e_max, num_energies);
    }
}
