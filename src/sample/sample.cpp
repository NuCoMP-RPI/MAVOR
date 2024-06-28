#include <iostream>
#include <chrono> 

#include "sample.hpp"

#include "runtime_variables.hpp"
#include "sample_cdf.hpp"
#include "sample_coeff.hpp"

void run_sample(){
    std::cout << sample_input_file << std::endl;
    std::cout << sample_output_file << std::endl;
    if (sample_cdf_file){sample_cdf();}
    if (sample_coeff_file){sample_coeff();}
}