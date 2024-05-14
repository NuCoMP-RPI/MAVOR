#include <iostream>
#include <vector>
#include <filesystem>
#include <map>

#include "process_otf.hpp"
#include "sab_file.hpp"

OTFData::OTFData(const std::string & directory){
    std::map<double, SabData, std::less<double>> files;
    for (const auto & entry : std::filesystem::directory_iterator(directory)){
        if (entry.is_regular_file()){
            SabData file_data(entry.path());
            files.insert(std::make_pair(file_data.temp, file_data));
        }
    }
    size_t num_files = files.size();

    // Extract the first files contents that should be the same across all files
    size_t k = 0;
    auto it = files.begin();
    za = it->second.za;
    mat = it->second.mat;
    a0 = it->second.a0;
    e_max = it->second.e_max;
    m0 = it->second.m0;
    free_xs = it->second.free_xs;
    bound_xs = it->second.bound_xs;
    inc_energy_grid = it->second.inc_energy_grid;
    beta_cdf_grid = it->second.beta_cdf_grid;
    beta_grid= it->second.beta_grid;
    alpha_cdf_grid = it->second.alpha_cdf_grid;

    // Initialize temp vector
    temps.resize(num_files);
    temps[k] = it->second.temp;

    // Initialize xs vector
    ii_xs.resize(inc_energy_grid.size(), std::vector<double>(num_files));

    // Initialize the vectors for storing the fit values (ordering needs to be <g1, g2, temps>)
    fit_beta_vals.resize(inc_energy_grid.size(), std::vector<std::vector<double>>(beta_cdf_grid.size(), std::vector<double>(num_files)));
    fit_alpha_vals.resize(beta_grid.size(), std::vector<std::vector<double>>(alpha_cdf_grid.size(), std::vector<double>(num_files)));

    // load in beta vals and xs
    for (size_t i; i<inc_energy_grid.size(); i++){
        ii_xs[i][k] = it->second.ii_xs[i];
        for (size_t j; j<beta_cdf_grid.size(); j++){
            fit_beta_vals[i][j][k] = it->second.fit_beta_vals[i][j];
        }
    }

    // load in alpha vals
    for (size_t i; i<beta_grid.size(); i++){
        for (size_t j; j<alpha_cdf_grid.size(); j++){
            fit_alpha_vals[i][j][k] = it->second.fit_alpha_vals[i][j];
        }
    }

    // increment counters
    it++;
    k++;

    // Read in the rest of the data
    while (it !=files.end())
    {
        __check__(za, it->second.za, "ZA");
        __check__(mat, it->second.mat, "MAT");
        __check__(a0, it->second.a0, "A0");
        __check__(e_max, it->second.e_max, "E_MAX");
        __check__(m0, it->second.m0, "M0");
        __check__(free_xs, it->second.free_xs, "FREE_XS");
        __check__(bound_xs, it->second.bound_xs, "BOUND_XS");
        __check__(inc_energy_grid, it->second.inc_energy_grid, "INCIDENT ENERGY GRID");
        __check__(beta_cdf_grid, it->second.beta_cdf_grid, "BETA CDF GRID");
        __check__(beta_grid, it->second.beta_grid, "BETA GRID");
        __check__(alpha_cdf_grid, it->second.alpha_cdf_grid, "ALPHA CDF GRID");
        temps[k] = it->second.temp;
        // load in beta vals
        for (size_t i; i<inc_energy_grid.size(); i++){
            ii_xs[i][k] = it->second.ii_xs[i];
            for (size_t j; j<beta_cdf_grid.size(); j++){
                fit_beta_vals[i][j][k] = it->second.fit_beta_vals[i][j];
            }
        }

        // load in alpha vals
        for (size_t i; i<beta_grid.size(); i++){
            for (size_t j; j<alpha_cdf_grid.size(); j++){
                fit_alpha_vals[i][j][k] = it->second.fit_alpha_vals[i][j];
            }
        }
        it++;
        k++;
    }
}

void OTFData::generate_coefficients(){
    __generate_A_matrix__();
}

void OTFData::__generate_A_matrix__(){

}

template<typename T> void OTFData::__check__(T const & val_1, T const & val_2, std::string const item_name){
    std::string error_message = item_name + " are not equal.  Terminating.";
    if (val_1 != val_2){
        throw std::runtime_error(error_message);
    }
}