#include <iostream>
#include <CLI/CLI.hpp>
#include <chrono>

#include "runtime_variables.hpp"
#include "njoy.hpp"
#include "sab.hpp"
#include "otf.hpp"
#include "sample.hpp"

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

    // DIST subcommand for SAB
    CLI::App &dist = *sab.add_subcommand("dist", "Returns a single distribution for use in comparisons.");
    dist.ignore_case();
    dist.add_option("-d,--dist", distribution_choice, "Desired distribution to calculate.") -> check(CLI::IsMember(distribution_choices)) -> required();
    dist.add_option("-i,--incident", dist_incident_energy, "Sets the incident energy to calculate the distribution.");
    dist.add_option("-o,--outgoing", dist_outgoing_energy, "Sets the outgoing energy to calculate the distribution.");
    dist.add_flag("-c,--convert", convert_to_eemu, "Convert the calculated distribution into the E,E',mu space.");

    // OTF subcommand
    CLI::App &otf = *mavor.add_subcommand("otf", "Generates the OTF sampling coefficients given unionized Sab TSL sampling distributions");
    otf.ignore_case();
    otf.add_option("-i, --input_directory", otf_input_directory, "Sets the location of the SAB sampling distributions.");
    otf.add_option("-o,--output_file", otf_output_file, "Sets the file name (and path) to store the OTF sampling coefficients.");
    otf.add_option("-g, --fit_group", fit_group, "Sets the fit group to use for defaults.");

    auto &xs_fit_override = *otf.add_option_group("Controls how the user wishes to override the XS fit.");
    auto basic_xs_override_flag = xs_fit_override.add_flag("--b_xs", basic_xs_fit_override, "Enables basic override options.");
    auto full_xs_override_flag = xs_fit_override.add_flag("--f_xs", full_xs_fit_override, "Enables full override options.");
    xs_fit_override.require_option(0,1);
    
    auto &beta_fit_override = *otf.add_option_group("Controls how the user wishes to override the Beta fit.");
    auto basic_beta_override_flag = beta_fit_override.add_flag("--b_beta", basic_beta_fit_override, "Enables basic override options.");
    auto full_beta_override_flag = beta_fit_override.add_flag("--f_beta", full_beta_fit_override, "Enables full override options.");
    beta_fit_override.require_option(0,1);

    auto &alpha_fit_override = *otf.add_option_group("Controls how the user wishes to override the Alpha fit.");
    auto basic_alpha_override_flag = alpha_fit_override.add_flag("--b_alpha", basic_alpha_fit_override, "Enables basic override options.");
    auto full_alpha_override_flag = alpha_fit_override.add_flag("--f_alpha", full_alpha_fit_override, "Enables full override options.");
    alpha_fit_override.require_option(0,1);

    auto &basic_xs = *otf.add_option_group("Basic XS fitting function override.");
    basic_xs.needs(basic_xs_override_flag);
    basic_xs.add_option("--p_xs", user_predefined_xs_fit, "Sets the predefined fit to use for XS.");
    basic_xs.add_option("--p_xs_num", user_predefined_xs_num_coeffs, "Sets the number of coefficient to generate.");

    auto &full_xs = *otf.add_option_group("Full XS fitting function override.");
    full_xs.needs(full_xs_override_flag);
    auto xs_num_coeffs_option = full_xs.add_option("--xs_num", xs_num_coeffs, "Sets the number of coefficient to generate.");
    auto xs_scale_temp_option = full_xs.add_option("--xs_scale", xs_scale_temp, "Sets whether to scale the temperatures before fitting.");
    auto xs_temp_scale_min_option = full_xs.add_option("--xs_scale_min", xs_temp_scale_min, "Sets the minimum value to scale the temperature.");
    auto xs_temp_scale_max_option = full_xs.add_option("--xs_scale_max", xs_temp_scale_max, "Sets the maximum value to scale the temperature");
    auto xs_fit_function_option = full_xs.add_option("--xs_fit_func", xs_basis_function, "Sets the fitting function to be used.");

    auto &basic_beta = *otf.add_option_group("Basic Beta fitting function override.");
    basic_beta.needs(basic_beta_override_flag);
    basic_beta.add_option("--p_beta", user_predefined_beta_fit, "Sets the predefined fit to use for Beta.");
    basic_beta.add_option("--p_beta_num", user_predefined_beta_num_coeffs, "Sets the number of coefficient to generate.");

    auto &full_beta = *otf.add_option_group("Override all BETA fitting function settings.");
    full_beta.needs(full_beta_override_flag);
    auto beta_num_coeffs_option = full_beta.add_option("--beta_num", beta_num_coeffs, "Sets the number of coefficient to generate.");
    auto beta_scale_temp_option = full_beta.add_option("--beta_scale", beta_scale_temp, "Sets whether to scale the temperatures before fitting.");
    auto beta_temp_scale_min_option = full_beta.add_option("--beta_scale_min", beta_temp_scale_min, "Sets the minimum value to scale the temperature.");
    auto beta_temp_scale_max_option = full_beta.add_option("--beta_scale_max", beta_temp_scale_max, "Sets the maximum value to scale the temperature");
    auto beta_fit_function_option = full_beta.add_option("--beta_fit_func", beta_basis_function, "Sets the fitting function to be used.");

    auto &basic_alpha = *otf.add_option_group("Basic Alpha fitting function override.");
    basic_alpha.needs(basic_alpha_override_flag);
    basic_alpha.add_option("--p_alpha", user_predefined_alpha_fit, "Sets the predefined fit to use for Alpha.");
    basic_alpha.add_option("--p_alpha_num", user_predefined_alpha_num_coeffs, "Sets the number of coefficient to generate.");

    auto &full_alpha = *otf.add_option_group("Override all ALPHA fitting function settings.");
    full_alpha.needs(full_alpha_override_flag);
    auto alpha_num_coeffs_option = full_alpha.add_option("--alpha_num", alpha_num_coeffs, "Sets the number of XS coefficient to generate.");
    auto alpha_scale_temp_option = full_alpha.add_option("--alpha_scale", alpha_scale_temp, "Sets whether to scale the temperatures before fitting.");
    auto alpha_temp_scale_min_option = full_alpha.add_option("--alpha_scale_min", alpha_temp_scale_min, "Sets the minimum value to scale the temperature.");
    auto alpha_temp_scale_max_option = full_alpha.add_option("--alpha_scale_max", alpha_temp_scale_max, "Sets the maximum value to scale the temperature");
    auto alpha_fit_function_option = full_alpha.add_option("--alpha_fit_func", alpha_basis_function, "Sets the fitting function to be used.");

    // sample subcommand
    CLI::App &sample = *mavor.add_subcommand("sample", "Samples the base CDF or the OTF distributions for comparisons.");
    sample.ignore_case();
    sample.add_option("-i,--input_file", sample_input_file, "Sets the file name (and path) to be sampled.");
    sample.add_option("-o,--output_file", sample_output_file, "Sets the file name (and path) to store the sampling results.");
    sample.add_option("-e,--inc_energy", sample_incident_energy, "Sets the incident energy to sample.");
    sample.add_option("-n,--number", sample_num_samples, "Sets the number of samples.");
    sample.add_option("-t,--temperature", sample_temperature, "Sets the temperature to sample for OTF data.");

    auto &sample_file = *sample.add_option_group("Tells Mavor what type of data is in the input file.");
    auto sample_coeff_option = sample_file.add_flag("--coeff", sample_coeff_file);
    auto sample_cdf_option = sample_file.add_flag("--cdf", sample_cdf_file);
    sample_file.require_option(1);

    auto &xs_eval_routine = *sample.add_option_group("Tells Mavor the evaluation routine to use when evaluating the XS basis function.  If none provided, Mavor will choose the default behavior.");
    auto sample_xs_naive_option = xs_eval_routine.add_flag("--xs_naive", sample_xs_naive_eval);
    auto sample_xs_optimal_option = xs_eval_routine.add_flag("--xs_optimal", sample_xs_optimal_eval);
    auto sample_xs_override_option = xs_eval_routine.add_option("--xs_override", sample_xs_override_evaluation_type);
    xs_eval_routine.require_option(0, 1);

    auto &beta_eval_routine = *sample.add_option_group("Tells Mavor the evaluation routine to use when evaluating the XS basis function.  If none provided, Mavor will choose the default behavior.");
    auto sample_beta_naive_option = beta_eval_routine.add_flag("--xs_naive", sample_beta_naive_eval);
    auto sample_beta_optimal_option = beta_eval_routine.add_flag("--xs_optimal", sample_beta_optimal_eval);
    auto sample_beta_override_option = beta_eval_routine.add_option("--xs_override", sample_beta_override_evaluation_type);
    beta_eval_routine.require_option(0, 1);

    auto &alpha_eval_routine = *sample.add_option_group("Tells Mavor the evaluation routine to use when evaluating the XS basis function.  If none provided, Mavor will choose the default behavior.");
    auto sample_alpha_naive_option = alpha_eval_routine.add_flag("--xs_naive", sample_alpha_naive_eval);
    auto sample_alpha_optimal_option = alpha_eval_routine.add_flag("--xs_optimal", sample_alpha_optimal_eval);
    auto sample_alpha_override_option = alpha_eval_routine.add_option("--xs_override", sample_alpha_override_evaluation_type);
    alpha_eval_routine.require_option(0, 1);

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
        if (dist.parsed()){
            override_sab = true;
            if (!silence){std::cout << "Overriding sab call and returning desired distribution." << std::endl;}
        }
        run_sab();
    }
    if (otf.parsed()){
        if (!silence){std::cout << "Running otf subroutines" << std::endl;}

        // Just look at this abomination, IDK how to make it any better
        if (*xs_num_coeffs_option){xs_override_num_coeffs = true;}
        if (*xs_scale_temp_option){xs_override_scale_temp = true;}
        if (*xs_temp_scale_min_option){xs_override_temp_scale_min = true;}
        if (*xs_temp_scale_max_option){xs_override_temp_scale_max = true;}
        if (*xs_fit_function_option){xs_override_fit_function = true;}
        if (*beta_num_coeffs_option){beta_override_num_coeffs = true;}
        if (*beta_scale_temp_option){beta_override_scale_temp = true;}
        if (*beta_temp_scale_min_option){beta_override_temp_scale_min = true;}
        if (*beta_temp_scale_max_option){beta_override_temp_scale_max = true;}
        if (*beta_fit_function_option){beta_override_fit_function = true;}
        if (*alpha_num_coeffs_option){alpha_override_num_coeffs = true;}
        if (*alpha_scale_temp_option){alpha_override_scale_temp = true;}
        if (*alpha_temp_scale_min_option){alpha_override_temp_scale_min = true;}
        if (*alpha_temp_scale_max_option){alpha_override_temp_scale_max = true;}
        if (*alpha_fit_function_option){alpha_override_fit_function = true;}

        run_otf();
    }

    if (sample.parsed()){
        if (!silence){std::cout << "Running sample subroutines" << std::endl;}
        if (*sample_cdf_option){sample_input_file = sample_cdf_test_file;}
        if (*sample_coeff_option){sample_input_file = sample_coeff_test_file;}

        if (*sample_xs_naive_option){sample_xs_naive_eval = true; sample_xs_default_eval = false;}
        if (*sample_xs_optimal_option){sample_xs_optimal_eval = true; sample_xs_default_eval = false;}        
        if (*sample_xs_override_option){sample_xs_override_eval = true; sample_xs_default_eval = false;}
        
        if (*sample_beta_naive_option){sample_beta_naive_eval = true; sample_beta_default_eval = false;}
        if (*sample_beta_optimal_option){sample_beta_optimal_eval = true; sample_beta_default_eval = false;}        
        if (*sample_beta_override_option){sample_beta_override_eval = true; sample_beta_default_eval = false;}
        
        if (*sample_alpha_naive_option){sample_alpha_naive_eval = true; sample_alpha_default_eval = false;}
        if (*sample_alpha_optimal_option){sample_alpha_optimal_eval = true; sample_alpha_default_eval = false;}        
        if (*sample_alpha_override_option){sample_alpha_override_eval = true; sample_alpha_default_eval = false;}

        run_sample();
    }
    
    auto main_process_end = std::chrono::high_resolution_clock::now();
    auto main_process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(main_process_end-main_process_start);
    if (!silence){
        std::cout << "Total elaspsed time | milliseconds " << main_process_duration.count() << std::endl;
    }
    return 0;
}