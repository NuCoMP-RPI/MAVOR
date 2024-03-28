#include <iostream>

#include "constants.hpp"
#include "file_read.hpp"

void print_array(std::vector<double> array){
    for(auto val: array){
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void process_file(const std::string& file_path){
    std::cout << file_path << '\n';
    TslData data(file_path);
    std::cout << data.lat << std::endl;
    std::cout << data.e_max << std::endl;
    print_array(data.return_scaled_alphas());
    std::cout << std::endl;
    print_array(data.return_scaled_betas());
    std::cout << std::endl;
    print_array(data.return_full_betas());
    std::cout << std::endl;
    print_array(data.return_full_scaled_betas());
    std::cout << std::endl;
}