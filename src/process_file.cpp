#include <iostream>

#include "constants.hpp"
#include "file_read.hpp"

void process_file(const std::string file_path){
    std::cout << file_path << '\n';
    read_file(file_path);

    std::cout << PI << '\n';
}