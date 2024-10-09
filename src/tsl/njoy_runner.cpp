#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <thread>

#include "njoy_runner.hpp"
#include "runtime_variables.hpp"

void execute_njoy(const std::filesystem::path &file, const int sim_num){
    std::filesystem::path sim_loc(tsl_njoy_sim_loc);
    sim_loc = sim_loc / std::to_string(sim_num);
    sim_loc = std::filesystem::absolute(sim_loc);
    std::filesystem::create_directory(sim_loc);
    std::filesystem::path njoy_exe(tsl_njoy_exe_loc);
    njoy_exe = std::filesystem::absolute(njoy_exe);
    std::filesystem::copy_options copy_set = std::filesystem::copy_options::overwrite_existing;
    std::filesystem::copy_file(njoy_exe, (sim_loc / "njoy"), copy_set);
    std::filesystem::copy_file(file, (sim_loc / "input"), copy_set);
    std::filesystem::path orig_work_dir = std::filesystem::current_path();
    std::filesystem::current_path(sim_loc);
    int _ = system("./njoy < input > out");
    std::filesystem::current_path(orig_work_dir);
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

    std::filesystem::create_directory(tsl_njoy_sim_loc);
    for (int i = 0; i < file_paths.size(); ++i) {
        execute_njoy(file_paths[i], i);
    }
}

