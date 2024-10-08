#include <iostream>
#include <chrono>

#include "njoy.hpp"
#include "runtime_variables.hpp"
#include "leapr_file.hpp"

void run_njoy(){
    if (!silence){
        std::cout << "Leapr file | " << njoy_leapr_file << std::endl;
    }
    
    auto file_read_start = std::chrono::high_resolution_clock::now();
    LeaprFile leapr_file(njoy_leapr_file);
    auto file_read_end = std::chrono::high_resolution_clock::now();
    auto file_read_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_read_end - file_read_start);
    if (!silence){
        std::cout << "Time to read in Leapr file | milliseconds " << file_read_duration.count() << std::endl;
    }

    auto write_start = std::chrono::high_resolution_clock::now();
    leapr_file.write_leapr_files();
    auto write_end = std::chrono::high_resolution_clock::now();
    auto write_duration = std::chrono::duration_cast<std::chrono::milliseconds>(write_end-write_start);
    if (!silence){
        std::cout << "Time to write LEAPR input files | milliseconds " << write_duration.count() << std::endl;
    }

    auto process_start = std::chrono::high_resolution_clock::now();
    // data.generate_coefficients();
    auto process_end = std::chrono::high_resolution_clock::now();
    auto process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(process_end-process_start);
    if (!silence){
        std::cout << "Time to run NJOY | milliseconds " << process_duration.count() << std::endl;
    }
}