#include <iostream>
#include <CLI/CLI.hpp>
#include <chrono>

#include "runtime_variables.hpp"
#include "njoy.hpp"
#include "sab.hpp"
#include "otf.hpp"

void print_name(){
    std::cout << R"(
__/\\\\____________/\\\\_____/\\\\\\\\\_____/\\\________/\\\_______/\\\\\_________/\\\\\\\\\_____________
__\/\\\\\\________/\\\\\\___/\\\\\\\\\\\\\__\/\\\_______\/\\\_____/\\\///\\\_____/\\\///////\\\__________
___\/\\\//\\\____/\\\//\\\__/\\\/////////\\\_\//\\\______/\\\____/\\\/__\///\\\__\/\\\_____\/\\\_________
____\/\\\\///\\\/\\\/_\/\\\_\/\\\_______\/\\\__\//\\\____/\\\____/\\\______\//\\\_\/\\\\\\\\\\\/_________
_____\/\\\__\///\\\/___\/\\\_\/\\\\\\\\\\\\\\\___\//\\\__/\\\____\/\\\_______\/\\\_\/\\\//////\\\________
______\/\\\____\///_____\/\\\_\/\\\/////////\\\____\//\\\/\\\_____\//\\\______/\\\__\/\\\____\//\\\______
_______\/\\\_____________\/\\\_\/\\\_______\/\\\_____\//\\\\\_______\///\\\__/\\\____\/\\\_____\//\\\____
________\/\\\_____________\/\\\_\/\\\_______\/\\\______\//\\\__________\///\\\\\/_____\/\\\______\//\\\__
_________\///______________\///__\///________\///________\///_____________\/////_______\///________\///__

)";
}

int main(int argc, char* argv[]){
    auto main_process_start = std::chrono::high_resolution_clock::now();

    // Set up main options
    CLI::App mavor{"Your place to make incoherent inelastic TSL sampling distributions."};
    argv = mavor.ensure_utf8(argv);
    mavor.set_help_all_flag("-H,--help_all", "Expands all help messages");
    mavor.add_flag("-s,--silent", silence, "Disables the terminal output");
    mavor.add_flag("-v,--verbose", verbose, "Enables additional terminal output (NOT SUPPORTED YET)");
    mavor.add_flag("-l,--log", log_run, "Enables logging (NOT SUPPORTED YET)");

    // NJOY subcommand
    CLI::App &njoy = *mavor.add_subcommand("njoy", "Runs NJOY and LEAPR to generate TSL data.");
    njoy.ignore_case();

    // SAB subcommand
    CLI::App &sab = *mavor.add_subcommand("sab", "Generates TSL sampling data given the output from LEAPR or similar tools.");
    sab.ignore_case();
    sab.add_option("-i,--input_file", sab_input_file, "Sets the file name (and path) to be processed.");
    sab.add_option("-o,--output_file", sab_output_file, "Sets the file name (and path) to store the sampling distributions.");
    sab.add_option("--beta_integration", beta_integration_scheme, "Controls how the integration in the beta direction is handled");
    sab.add_option("--beta_interpolation", beta_interpolation_scheme, "Controls how the interpolation in the beta direction is handled");
    sab.add_option("--alpha_integration", alpha_integration_scheme, "Controls how the integration in the alpha direction is handled");
    sab.add_option("--alpha_interpolation", alpha_interpolation_scheme, "Controls how the interpolation in the alpha direction is handled");
    sab.add_option("--beta_cdf_points", num_beta_cdf_points, "Sets the number of CDF points to be used in fitting the beta sampling distributions");
    sab.add_option("--beta_cdf_extent", beta_cdf_extent, "Sets the extent of the logistic regression function used to generate the beta CDF points.  The higher the value, the denser the points close to 0 and 1");
    sab.add_option("--alpha_cdf_points", num_alpha_cdf_points, "Sets the number of CDF points to be used in fitting the beta sampling distributions");
    sab.add_option("--alpha_cdf_extent", alpha_cdf_extent, "Sets the extent fo the logistic regression function used to generate the alpha CDF points.  The higher the value, the denser the points close to 0 and 1");
    sab.add_option("--beta_max", beta_max, "Sets the maximum beta value to consider.");    
    sab.add_option("--sct_cutoff", sct_cutoff, "Sets the cutoff for the transition to the Short Collision Time Approximation.");
    sab.add_option("--alpha_min", alpha_min, "Sets the minimum integration alpha value");
    sab.add_option("--e_min", e_min, "Sets the minimum incident energy to consider.");
    sab.add_option("--num_energies", num_energies, "Sets the number of energies that are used to initialize the incident energy grid.");
    auto &energy = *sab.add_option_group("Incident Energy Settings", "Sets how the incident energy grid is determined");
    auto user_energy_option = energy.add_option("-u,--user_energy_grid", energy_grid_loc, "Sets the location for a user defined energy grid to be used");
    auto predefined_energy_option = energy.add_flag("-p,--predefined_energy_grid", use_internal_energy_grid, "Tells the program to use the predefined energy grid");
    energy.require_option(0,1);

    // OTF subcommand
    CLI::App &otf = *mavor.add_subcommand("otf", "Generates the OTF sampling coefficients given unionized Sab TSL sampling distributions");
    otf.ignore_case();

    // Parse the command line arguments
    CLI11_PARSE(mavor, argc, argv);


    // Print the header to terminal
    if (!silence){
        print_name();
    }

    if (njoy.parsed()){
        if (!silence){std::cout << "Running njoy subroutines" << std::endl;}
        run_njoy();
    }
    if (sab.parsed()){
        if (!silence){std::cout << "Running sab subroutines" << std::endl;}
        if (*user_energy_option){use_external_energy_grid = true;}
        run_sab();
    }
    if (otf.parsed()){
        if (!silence){std::cout << "Running otf subroutines" << std::endl;}
        run_otf();
    }
    
    auto main_process_end = std::chrono::high_resolution_clock::now();
    auto main_process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(main_process_end-main_process_start);
    if (!silence){
        std::cout << "Total elaspsed time | milliseconds " << main_process_duration.count() << std::endl;
    }
    return 0;
}