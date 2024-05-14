#include <iostream>
#include <chrono>

#include "otf.hpp"
#include "runtime_variables.hpp"
#include "process_otf.hpp"

void run_otf(){
    if (!silence){
        std::cout << "Input Directory | " << otf_input_directory << std::endl;
    }
    
    auto file_read_start = std::chrono::high_resolution_clock::now();
    OTFData data(otf_input_directory);
    auto file_read_end = std::chrono::high_resolution_clock::now();
    auto file_read_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_read_end - file_read_start);
    if (!silence){
        std::cout << "Time to read in SAB sampling distributions | milliseconds " << file_read_duration.count() << std::endl;
    }

    auto process_start = std::chrono::high_resolution_clock::now();
    data.generate_coefficients();
    auto process_end = std::chrono::high_resolution_clock::now();
    auto process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(process_end-process_start);
    if (!silence){
        std::cout << "Time to calculate the OTF coefficients | milliseconds " << process_duration.count() << std::endl;
    }

    if (!silence){
        std::cout << "Coefficients File | " << otf_output_file << '\n';
    }
    auto file_write_start = std::chrono::high_resolution_clock::now();
    // write coefficients file
    auto file_write_end = std::chrono::high_resolution_clock::now();
    auto file_write_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_write_end-file_write_start);
    if (!silence){
        std::cout << "Time to write the OTF coefficients | milliseconds " << file_write_duration.count() << std::endl;
    }
}