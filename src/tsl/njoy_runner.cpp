#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <thread>

#include "njoy_runner.hpp"
#include "runtime_variables.hpp"
#include "file_read.hpp"

void execute_njoy(const std::filesystem::path &file, const int sim_num){
    std::filesystem::path sim_loc(tsl_njoy_sim_loc);
    sim_loc = sim_loc / std::to_string(sim_num);
    sim_loc = std::filesystem::absolute(sim_loc);
    std::string command = "cd " + sim_loc.string() + " && ./njoy < input > out";
    int _ = system(command.c_str());
    std::filesystem::path endf_tape = sim_loc / "tape20";
    TslFileData endf_data(endf_tape, "endf");
    std::filesystem::path hdf5_write_loc(tsl_njoy_results_dir);
    std::filesystem::path hdf5_file = hdf5_write_loc / (file.stem().string() + "_njoy_results.h5");
    endf_data.write_to_hdf5(hdf5_file);
    std::filesystem::remove_all(sim_loc);
}

void njoy_runner(){
    std::vector<std::filesystem::path> file_paths;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(tsl_leapr_write_dir)) {
            if (entry.is_regular_file()){
                file_paths.push_back(std::filesystem::absolute(entry.path()));
            }
        }
    } catch (const std::filesystem::filesystem_error& err) {
        std::cerr << "Error: " << err.what() << std::endl;
    }
    if (std::filesystem::exists(tsl_njoy_sim_loc)){std::filesystem::remove_all(tsl_njoy_sim_loc);}
    std::filesystem::create_directory(tsl_njoy_sim_loc);
    std::filesystem::create_directory(tsl_njoy_results_dir);

    if (!silence){std::cout << "Number of leapr files to run | " << file_paths.size() << std::endl;}

    // Create the simulation directories and copy njoy exe before parallel call
    std::filesystem::path parent_sim_loc(tsl_njoy_sim_loc);
    std::filesystem::path njoy_exe_src(tsl_njoy_exe_loc);
    njoy_exe_src = std::filesystem::absolute(njoy_exe_src);
    if (!silence){std::cout << "NJOY executable | " << njoy_exe_src << std::endl;}
    for (int sim_num = 0; sim_num < file_paths.size(); ++sim_num){
        std::filesystem::path file = file_paths[sim_num];
        std::filesystem::path sim_loc = parent_sim_loc / std::to_string(sim_num);
        sim_loc = std::filesystem::absolute(sim_loc);
        std::filesystem::create_directory(sim_loc);
        std::filesystem::copy_file(njoy_exe_src, sim_loc / "njoy");
        std::filesystem::copy_file(file, sim_loc / "input");
    }

    #pragma omp parallel for
    for (int i = 0; i < file_paths.size(); ++i) {
        execute_njoy(file_paths[i], i);
    }
}