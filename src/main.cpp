#include <iostream>
#include <CLI/CLI.hpp>
#include <chrono>

#include "process_file.hpp"
#include "runtime_variables.hpp"

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
    // Parse the command line arguments
    CLI::App mavor{"Generates S(a,b) TSL sampling distributions."};
    argv = mavor.ensure_utf8(argv);
    mavor.add_option("-i,--input_file", input_file, "Sets the file name (and path) to be processed.");
    mavor.add_option("-o,--output_file", output_file, "Sets the file name (and path) to store the sampling distributions.");
    mavor.add_option("--beta_integration", beta_integration_scheme, "Controls how the integration in the beta direction is handled");
    mavor.add_option("--beta_interpolation", beta_interpolation_scheme, "Controls how the interpolation in the beta direction is handled");
    mavor.add_option("--alpha_integration", alpha_integration_scheme, "Controls how the integration in the alpha direction is handled");
    mavor.add_option("--alpha_interpolation", alpha_interpolation_scheme, "Controls how the interpolation in the alpha direction is handled");
    mavor.add_option("--beta_cdf_points", num_beta_cdf_points, "Sets the number of CDF points to be used in fitting the beta sampling distributions");
    mavor.add_option("--beta_cdf_extent", beta_cdf_extent, "Sets the extent of the logistic regression function used to generate the beta CDF points.  The higher the value, the denser the points close to 0 and 1");
    mavor.add_option("--alpha_cdf_points", num_alpha_cdf_points, "Sets the number of CDF points to be used in fitting the beta sampling distributions");
    mavor.add_option("--alpha_cdf_extent", alpha_cdf_extent, "Sets the extent fo the logistic regression function used to generate the alpha CDF points.  The higher the value, the denser the points close to 0 and 1");
    mavor.add_flag("-s,--silent", silence, "Disables the terminal output");
    mavor.add_flag("-v,--verbose", verbose, "Enables additional terminal output (NOT SUPPORTED YET)");
    mavor.add_flag("-l,--log", log_run, "Enables logging (NOT SUPPORTED YET)");
    mavor.add_flag("-n,--no_process", no_process, "Disables the processing of the data.  Allows for immediate program termination.");
    CLI11_PARSE(mavor, argc, argv);

    // Print the header to terminal
    if (!silence){
        print_name();
    }

    // Process the file    
    if (!no_process){
        process_file(input_file, output_file);
    }
    auto main_process_end = std::chrono::high_resolution_clock::now();
    auto main_process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(main_process_end-main_process_start);
    if (!silence){
        std::cout << "Time to process the file | milliseconds " << main_process_duration.count() << std::endl;
    }
    return 0;
}