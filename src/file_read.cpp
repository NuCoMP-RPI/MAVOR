#include <iostream>

#include "H5Cpp.h"

void read_file(const std::string file_path){
    std::cout << file_path << '\n';

    // Initialize the HDF5 library
    H5::H5Library::open();

    // Close the HDF5 library
    H5::H5Library::close();
}