#include <iostream>

#include "constants.hpp"
#include "file_read.hpp"

void print_array(std::vector<double> array){
    for(auto val: array){
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void print_matrix(std::vector<std::vector<double>> matrix){
    for(auto vec:matrix){
        for(auto val:vec){
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void process_file(const std::string& file_path){
    std::cout << file_path << '\n';
    TslFileData data(file_path);
}