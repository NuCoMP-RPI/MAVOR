#include <iostream>
#include <chrono>
#include <tuple>
#include <fstream>
#include <iomanip>

#include "runtime_variables.hpp"
#include "sab.hpp"
#include "file_read.hpp"
#include "file_write.hpp"

void write_vectors_to_file(const std::vector<double>& x, const std::vector<double>& y, const std::string& filename) {
    std::ofstream outfile(filename);
    outfile << std::scientific << std::setprecision(15);
    for (size_t i = 0; i < x.size(); ++i) {
        outfile << x[i] << "," << y[i] << "\n";
    }
    outfile.close();
}

void run_sab(){
    if (!silence){
        std::cout << "Input file to process | " << sab_input_file << '\n';
    }

    auto file_read_start = std::chrono::high_resolution_clock::now();
    TslFileData file_data(sab_input_file);
    DistData dist_data(file_data);
    auto file_read_end  = std::chrono::high_resolution_clock::now();
    auto file_read_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_read_end - file_read_start);
    if (!silence){
        std::cout << "Time to read in file and prepare data | milliseconds " << file_read_duration.count() << std::endl;
    }

    if (!override_sab){
        auto process_start = std::chrono::high_resolution_clock::now();
        dist_data.calculate_sampling_dists();
        auto process_end = std::chrono::high_resolution_clock::now();
        auto process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(process_end-process_start);
        if (!silence){
            std::cout << "Time to calculate the sampling distributions | milliseconds " << process_duration.count() << std::endl;
        }

        if (!silence){
            std::cout << "Results file | " << sab_output_file << '\n';
        }
        auto file_write_start = std::chrono::high_resolution_clock::now();
        write_sampling_data(dist_data, sab_output_file);
        auto file_write_end = std::chrono::high_resolution_clock::now();
        auto file_write_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_write_end-file_write_start);
        if (!silence){
            std::cout << "Time to write the sampling distributions | milliseconds " << file_write_duration.count() << std::endl;
        }
    }
    else{
        auto process_start = std::chrono::high_resolution_clock::now();
        std::vector<double> x,y;
        double beta;
        switch (distribution_choice)
        {
        case 1:
            if (!silence){std::cout << "Calculating Cross Section." << std::endl;}
            std::tie(x,y) = dist_data.return_linearized_ii_xs();
            break;
        case 2:
            if (!silence){std::cout << "Calculating Energy Transfer." << std::endl;}
            std::tie(x,y) = dist_data.return_linearized_beta_pdf(dist_incident_energy);
            if (convert_to_eemu){
                x = dist_data.betas_to_outgoing_energies(dist_incident_energy, x);
            }
            break;
        case 3:
            beta = dist_data.return_beta(dist_incident_energy, dist_outgoing_energy);
            if (!silence){
                std::cout << "Calculation Momentum Transfer." << std::endl;
                std::cout << "Desired Beta value: " << beta << std::endl;
            }
            std::tie(x,y) = dist_data.return_viable_linearized_alpha_pdf(dist_incident_energy, beta);
            if (convert_to_eemu){
                x = dist_data.alphas_to_scatting_angles(dist_incident_energy, dist_outgoing_energy, x);
            }
            break;
        default:
            throw std::runtime_error("Unknown Sampling Distribution Choice. IDK how you got here.");
        }
        if (!silence){std::cout << "Results file | " << sab_output_file << '\n';}
        write_vectors_to_file(x,y, sab_output_file);
        auto process_end = std::chrono::high_resolution_clock::now();
        auto process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(process_end-process_start);
        if (!silence){
            std::cout << "Time to calculate and write distribution | milliseconds " << process_duration.count() << std::endl;
        }
    }
}