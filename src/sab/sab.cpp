#include <iostream>
#include <chrono>

#include "runtime_variables.hpp"
#include "sab.hpp"
#include "file_read.hpp"
#include "file_write.hpp"

void run_sab(){
    std::cout << "Hello from SAB" << std::endl;
    if (!silence){
        std::cout << "Input file to process | " << input_file << '\n';
    }

    auto file_read_start = std::chrono::high_resolution_clock::now();
    TslFileData file_data(input_file);
    DistData dist_data(file_data);
    auto file_read_end  = std::chrono::high_resolution_clock::now();
    auto file_read_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_read_end - file_read_start);
    if (!silence){
        std::cout << "Time to read in file and prepare data | milliseconds " << file_read_duration.count() << std::endl;
    }

    auto process_start = std::chrono::high_resolution_clock::now();
    dist_data.calculate_sampling_dists();
    auto process_end = std::chrono::high_resolution_clock::now();
    auto process_duration = std::chrono::duration_cast<std::chrono::milliseconds>(process_end-process_start);
    if (!silence){
        std::cout << "Time to calculate the sampling distributions | milliseconds " << process_duration.count() << std::endl;
    }

    if (!silence){
        std::cout << "Results file | " << output_file << '\n';
    }
    auto file_write_start = std::chrono::high_resolution_clock::now();
    write_sampling_data(dist_data, output_file);
    auto file_write_end = std::chrono::high_resolution_clock::now();
    auto file_write_duration = std::chrono::duration_cast<std::chrono::milliseconds>(file_write_end-file_write_start);
    if (!silence){
        std::cout << "Time to write the sampling distributions | milliseconds " << file_write_duration.count() << std::endl;
    }
}